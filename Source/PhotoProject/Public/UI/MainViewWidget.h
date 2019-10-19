// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UMainViewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainViewWidget")
	class ULoopViewWidget* LoopView1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainViewWidget")
	class ULoopViewWidget* LoopView2;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainViewWidget")
	class ULoopViewWidget* LoopView3;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainViewWidget")
	class ULoopViewWidget* LoopView4;
};
