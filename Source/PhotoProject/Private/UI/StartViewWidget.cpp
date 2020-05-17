// Fill out your copyright notice in the Description page of Project Settings.

#include "StartViewWidget.h"
#include "DataManager.h"


void UStartViewWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FDataManager::GetInstance().LoadAllData();
	FDataManager::GetInstance().LoadStartVideoFrames();
}
