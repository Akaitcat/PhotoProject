// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Defs/PersonData.h"
#include "LoopViewItemWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnLoopItemClicked, ULoopViewItemWidget*);

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API ULoopViewItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "LoopViewItemWidget")
	void InitData(int32 nDataIndex, UObject* pData);
	void InitDataInternal(int32 nDataIndex, UPersonData* pData);
	
	void SetVisible(bool bVisible);
	UFUNCTION(BlueprintCallable, Category = "LoopViewItemWidget")
	void ForwardItemClick();
	FOnLoopItemClicked& OnItemClicked() { return OnItemClickedEvent; }
public:
	UPersonData* m_PersonData;
	int32 m_nRowIndex;
	int32 m_nColIndex;
private:
	FOnLoopItemClicked OnItemClickedEvent;
};
