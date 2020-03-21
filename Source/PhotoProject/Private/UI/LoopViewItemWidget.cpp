// Fill out your copyright notice in the Description page of Project Settings.

#include "LoopViewItemWidget.h"


void ULoopViewItemWidget::InitDataInternal(int32 nDataIndex, UPersonData* pData)
{
	m_PersonData = pData;
	InitData(nDataIndex, pData);
}

void ULoopViewItemWidget::SetVisible(bool bVisible)
{
	SetVisibility(bVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void ULoopViewItemWidget::ForwardItemClick()
{
	OnItemClickedEvent.Execute(this);
}
