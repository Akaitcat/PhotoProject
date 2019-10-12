// Fill out your copyright notice in the Description page of Project Settings.

#include "LoopViewItemWidget.h"


void ULoopViewItemWidget::SetVisible(bool bVisible)
{
	SetVisibility(bVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}
