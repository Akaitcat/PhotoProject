// Fill out your copyright notice in the Description page of Project Settings.

#include "LoopViewWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "LoopViewItemWidget.h"
DEFINE_STAT(STAT_LoopViewWidget_UpdateLoop);

bool ULoopViewWidget::Initialize()
{
	Super::Initialize();
	if (ContainerPanel) {
		UCanvasPanelSlot* ContainerSlot = Cast<UCanvasPanelSlot>(ContainerPanel->Slot);
		ensureMsgf(ContainerSlot, TEXT("LoopViewWidget::ContainerPanel's Slot must be UCanvasPanelSlot"));
		if (ContainerSlot&&m_nColumnNum> 0) {
			m_ContainerSize = ContainerSlot->GetSize();
		}
	}
	return true;
}

void ULoopViewWidget::InitData(const TArray<UObject*>& dataArray)
{
	m_DataArray = dataArray;
	InitChildrenItems();
}

void ULoopViewWidget::InitChildrenItems()
{
	m_CurrentStartIndex = 0;
	m_ItemChildren.Empty();
	int32 nContainerRowNum = FMath::CeilToInt(m_ContainerSize.Y /m_ChildSize.Y);
	int32 nNecessaryChildrenNum = m_DataArray.Num()>m_ContainerChildNum?(nContainerRowNum + 2)*m_nColumnNum : m_DataArray.Num();
	for (int32 i = 0; i < nNecessaryChildrenNum; i++) {
		ULoopViewItemWidget* pItem = CreateChild();
		UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(pItem->Slot);
		m_ItemChildren.Add(pItem);
		// 最后面两列用于无缝滚动
		pItem->m_nRowIndex = i / m_nColumnNum;
		pItem->m_nColIndex = i % m_nColumnNum;
		if (i < m_DataArray.Num()) {
			pItem->InitData(i, m_DataArray[i]);
		}
		else {
			pItem->SetVisible(false);
		}
		// 初始化位置
		FVector2D itemPosition;
		itemPosition.X = pItem->m_nColIndex * m_ChildSize.X;
		itemPosition.Y = pItem->m_nRowIndex * m_ChildSize.Y;
		pChildSlot->SetPosition(itemPosition);
	}
}

void ULoopViewWidget::MoveLayoutFirstToEnd()
{
	int32 nContainerRowNum = FMath::CeilToInt(m_ContainerSize.Y / m_ChildSize.Y);
	for (auto pChild : m_ItemChildren) {
		UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(pChild->Slot);
		pChild->m_nRowIndex--;
		if (pChild->m_nRowIndex==-1) {
			pChild->m_nRowIndex = nContainerRowNum + 1;
			int32 nDataIndex = m_CurrentStartIndex;
			for (int32 i = 0; i < nContainerRowNum + 2; i++) {
				nDataIndex += m_nColumnNum;
				if (nDataIndex >= m_DataArray.Num()) {
					nDataIndex = 0;
				}
			}
			nDataIndex += pChild->m_nColIndex;
			if (nDataIndex < m_DataArray.Num()) {
				pChild->SetVisible(true);
				pChild->InitData(nDataIndex, m_DataArray[nDataIndex]);
			}
			else {
				pChild->SetVisible(false);
			}
		}
		FVector2D newPosition = pChildSlot->GetPosition();
		newPosition.Y = m_ChildSize.Y*(pChild->m_nRowIndex);
		pChildSlot->SetPosition(newPosition);
	}
	m_CurrentStartIndex += m_nColumnNum;
	if (m_CurrentStartIndex >= m_DataArray.Num()) {
		m_CurrentStartIndex = 0;
	}
}

void ULoopViewWidget::NativeTick(const FGeometry& InGeometry, float fDeltaTime)
{
	Super::NativeTick(InGeometry, fDeltaTime);
	if (m_LoopAnimationData.IsPlaying()) {
		UpdateLoop(fDeltaTime);
	}
}

void ULoopViewWidget::BeginLoop(float fSpeed)
{
	if (m_DataArray.Num() > m_ContainerChildNum) {
		m_LoopAnimationData.m_fAnimateSpeed = fSpeed;
		m_LoopAnimationData.Play();
	}
}

void ULoopViewWidget::PauseLoop()
{
	m_LoopAnimationData.Pause();
}

void ULoopViewWidget::UpdateLoop(float fDeltaTime)
{
	SCOPE_CYCLE_COUNTER(STAT_LoopViewWidget_UpdateLoop);
	UCanvasPanelSlot* pContainerSlot = Cast<UCanvasPanelSlot>(ContainerPanel->Slot);
	FVector2D containerPosition = pContainerSlot->GetPosition();
	containerPosition.Y -= m_LoopAnimationData.m_fAnimateSpeed;
	if (containerPosition.Y < -m_ChildSize.Y) {
		containerPosition.Y = containerPosition.Y + m_ChildSize.Y;
		MoveLayoutFirstToEnd();
	}
	pContainerSlot->SetPosition(containerPosition);
}

void ULoopViewWidget::EndLoop()
{
	m_LoopAnimationData.Stop();
}

ULoopViewItemWidget* ULoopViewWidget::CreateChild()
{
	if (GEngine) {
		APlayerController* pController = GEngine->GetFirstLocalPlayerController(GetWorld());
		ULoopViewItemWidget* newItem = CreateWidget<ULoopViewItemWidget>(pController, ChildWidgetClass);
		ContainerPanel->AddChild(newItem);
		UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(newItem->Slot);
		pChildSlot->SetSize(m_ChildSize);
		return newItem;
	}
	return nullptr;
}
