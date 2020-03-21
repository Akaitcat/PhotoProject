// Fill out your copyright notice in the Description page of Project Settings.

#include "LoopViewWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "LoopViewItemWidget.h"
#include "Defs/PersonData.h"
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
	m_nCurrentDataIndex = 0;
	InitChildrenItems();
	// ResetAppearance
	UCanvasPanelSlot* pContainerSlot = Cast<UCanvasPanelSlot>(ContainerPanel->Slot);
	if (pContainerSlot) {
		pContainerSlot->SetPosition(FVector2D(0,0));
	}
	}

void ULoopViewWidget::InitChildrenItems()
{
	ContainerPanel->ClearChildren();
	m_NodeMatrix.Empty();
	int32 nContainerRowNum = FMath::CeilToInt(m_ContainerSize.Y / m_ChildSize.Y);

	for (int32 i = 0; i < nContainerRowNum + 2; i++) {
		TArray<int32> newRow;
		newRow.AddZeroed(m_nColumnNum);
		m_NodeMatrix.Add(newRow);
	}
	FilllMatrix();
}


void ULoopViewWidget::FilllMatrix()
{
	for (int32 nRow = 0; nRow < m_NodeMatrix.Num()-1; nRow++) {
		for (int32 nCol = 0; nCol < m_NodeMatrix[nRow].Num(); nCol++) {
			if (m_NodeMatrix[nRow][nCol] == 0) {// 如果有坑位， 则取数据填坑
				UPersonData* pPersonData = Cast<UPersonData>(m_DataArray[m_nCurrentDataIndex]);
				check(pPersonData);
				bool bBigIcon = !pPersonData->m_strLocalVideoPath.IsEmpty();
				bool bSpaceEnough = false;
				if(bBigIcon){// 如果是大萝卜, 则占据4个萝卜坑
					if ((nCol + 1) < m_NodeMatrix[nRow].Num()) {
						m_NodeMatrix[nRow][nCol] = 2;
						m_NodeMatrix[nRow][nCol+1] = 2;
						m_NodeMatrix[nRow+1][nCol] = 2;
						m_NodeMatrix[nRow+1][nCol+1] = 2;
						bSpaceEnough = true;
					}
					else {// 如果只剩下一列了, 则使当前坑位失效，跳过这个坑
						m_NodeMatrix[nRow][nCol] = -1;
					}
				}
				else {// 如果是小萝卜，直接填到坑里
					m_NodeMatrix[nRow][nCol] = 1;
					bSpaceEnough = true;
				}
				if (bSpaceEnough) {
					ULoopViewItemWidget* pNewItem = CreateChild(nRow, nCol);
					pNewItem->InitData(m_nCurrentDataIndex, pPersonData);
					m_nCurrentDataIndex++;
					if (m_nCurrentDataIndex >= m_DataArray.Num()) {
						m_nCurrentDataIndex = 0;
					}
				}
			}
		}
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
	if (containerPosition.Y <= -m_ChildSize.Y) {
		containerPosition.Y = containerPosition.Y + m_ChildSize.Y;
		for (int32 i = ContainerPanel->GetChildrenCount() -1; i >=0; i--) {
			ULoopViewItemWidget* pChild = Cast<ULoopViewItemWidget>(ContainerPanel->GetChildAt(i));
			UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(pChild->Slot);
			FVector2D childPosition = pChildSlot->GetPosition();
			if (childPosition.Y < -m_ChildSize.Y*2 -0.0001f) {
				ContainerPanel->RemoveChildAt(i);
			}
		}
		for (int32 i = 0; i < ContainerPanel->GetChildrenCount(); i++) {
			ULoopViewItemWidget* pChild = Cast<ULoopViewItemWidget>(ContainerPanel->GetChildAt(i));
			UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(pChild->Slot);
			FVector2D childPosition = pChildSlot->GetPosition();
			childPosition.Y -= m_ChildSize.Y;
			pChildSlot->SetPosition(childPosition);
		}

		m_NodeMatrix.RemoveAt(0);
		TArray<int32> newRow;
		newRow.AddZeroed(m_nColumnNum);
		m_NodeMatrix.Add(newRow);
		FilllMatrix();
	}
	pContainerSlot->SetPosition(containerPosition);
}

void ULoopViewWidget::EndLoop()
{
	m_LoopAnimationData.Stop();
}

ULoopViewItemWidget* ULoopViewWidget::CreateChild(int32 nRow, int32 nCol)
{
	ULoopViewItemWidget* newItem = CreateWidget<ULoopViewItemWidget>(GetOwningPlayer(), ChildWidgetClass);
	ContainerPanel->AddChild(newItem);
	UCanvasPanelSlot* pChildSlot = Cast<UCanvasPanelSlot>(newItem->Slot);
	pChildSlot->SetSize(m_ChildSize);
	pChildSlot->SetPosition(FVector2D(nCol * m_ChildSize.X, nRow * m_ChildSize.Y));
	newItem->m_nRowIndex = nRow;
	newItem->m_nColIndex = nCol;
	newItem->OnItemClicked().BindUObject(this,&ULoopViewWidget::HandleItemClicked);
	return newItem;
}
