// Fill out your copyright notice in the Description page of Project Settings.

#include "MainViewWidget.h"
#include "DataManager.h"
#include "LoopViewWidget.h"
#include "SlateBasics.h"



void UMainViewWidget::NativeConstruct()
{

	TArray<UObject*> dataArray1 = FDataManager::GetInstance().GetData(TEXT("2006"));
	TArray<UObject*> dataArray2 = FDataManager::GetInstance().GetData(TEXT("2011"));
	TArray<UObject*> dataArray3 = FDataManager::GetInstance().GetData(TEXT("2016"));
	TArray<UObject*> dataArray4 = FDataManager::GetInstance().GetData(TEXT("2020"));
	LoopView1->InitData(dataArray1);
	LoopView1->BeginLoop(1.0f);
	LoopView2->InitData(dataArray2);
	LoopView2->BeginLoop(1.0f);
	LoopView3->InitData(dataArray3);
	LoopView3->BeginLoop(1.0f);
	LoopView4->InitData(dataArray4);
	LoopView4->BeginLoop(1.0f);
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
