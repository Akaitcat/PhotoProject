// Fill out your copyright notice in the Description page of Project Settings.

#include "MainViewWidget.h"
#include "DataManager.h"
#include "LoopViewWidget.h"
#include "SlateBasics.h"



void UMainViewWidget::NativeConstruct()
{
	TArray<UObject*> dataArray = FDataManager::GetInstance().GetAllData();
	LoopView1->InitData(dataArray);
	LoopView1->BeginLoop(1.0f);
	Super::NativeConstruct();
}

void UMainViewWidget::NativeTick(const FGeometry& InGeometry, float fDeltaTime)
{
	Super::NativeTick(InGeometry, fDeltaTime);
	if (GetVisibility() != ESlateVisibility::Collapsed&& GetVisibility() != ESlateVisibility::Hidden) {
		double delta = FSlateApplication::Get().GetCurrentTime() - FSlateApplication::Get().GetLastUserInteractionTime();
		if (delta > 180) {
			OnIdleOver();
		}
	}
}