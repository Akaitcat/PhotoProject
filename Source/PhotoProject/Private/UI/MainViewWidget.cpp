// Fill out your copyright notice in the Description page of Project Settings.

#include "MainViewWidget.h"
#include "DataManager.h"
#include "LoopViewWidget.h"



void UMainViewWidget::NativeConstruct()
{
	TArray<UObject*> testDataArray = FDataManager::GetInstance().GetTestData();
	LoopView1->InitData(testDataArray);
	LoopView1->BeginLoop(1.0f);
	LoopView2->InitData(testDataArray);
	LoopView2->BeginLoop(1.0f);
	LoopView3->InitData(testDataArray);
	LoopView3->BeginLoop(1.0f);
	Super::NativeConstruct();
}
