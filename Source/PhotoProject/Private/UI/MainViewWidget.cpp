// Fill out your copyright notice in the Description page of Project Settings.

#include "MainViewWidget.h"
#include "DataManager.h"
#include "LoopViewWidget.h"



void UMainViewWidget::NativeConstruct()
{
	TArray<UObject*> dataArray1 = FDataManager::GetInstance().GetData(TEXT("2011"));
	LoopView1->InitData(dataArray1);
	LoopView1->BeginLoop(1.0f);
	LoopView2->InitData(dataArray1);
	LoopView2->BeginLoop(1.0f);
	LoopView3->InitData(dataArray1);
	LoopView3->BeginLoop(1.0f);
	Super::NativeConstruct();
}
