// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoopViewItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API ULoopViewItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent,Category = "LoopViewItemWidget")
	void InitData(int32 nDataIndex, UObject* pData);
	
	void SetVisible(bool bVisible);
public:
	int32 m_nRowIndex;
	int32 m_nColIndex;
};
