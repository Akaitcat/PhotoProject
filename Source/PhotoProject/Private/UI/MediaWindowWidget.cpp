// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaWindowWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

FReply UMediaWindowWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchStarted(InGeometry, InGestureEvent);
	m_CurrentHolder = InGestureEvent.GetPointerIndex();
	m_StartPosition = InGestureEvent.GetScreenSpacePosition();
	UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(WindowPanel->Slot);
	if (pSlot) {
		m_StartSlotPosition = pSlot->GetPosition();
		FGeometry parentGeometry = WindowPanel->GetParent()->GetCachedGeometry();
		m_StartSlotPosition = parentGeometry.LocalToAbsolute(m_StartSlotPosition);
	}
	return FReply::Handled();
}

FReply UMediaWindowWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchEnded(InGeometry, InGestureEvent);
	if (m_CurrentHolder > 10000|| m_CurrentHolder!= InGestureEvent.GetPointerIndex()) {
		return FReply::Handled();
	}
	m_CurrentHolder = 99999;
	return FReply::Handled();
}

FReply UMediaWindowWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchMoved(InGeometry, InGestureEvent);
	if (m_CurrentHolder > 10000 || m_CurrentHolder != InGestureEvent.GetPointerIndex()) {
		return FReply::Handled();
	}
	FVector2D currentPosition = InGestureEvent.GetScreenSpacePosition();
	FVector2D newPosition = currentPosition - m_StartPosition+m_StartSlotPosition;
	FGeometry parentGeometry = WindowPanel->GetParent()->GetCachedGeometry();
	newPosition = parentGeometry.AbsoluteToLocal(newPosition);
	UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(WindowPanel->Slot);
	if (pSlot) {
		pSlot->SetPosition(newPosition);
	}
	return FReply::Handled();
}
