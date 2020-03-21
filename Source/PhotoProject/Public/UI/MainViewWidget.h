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
	virtual void NativeTick(const FGeometry& InGeometry,float fDeltaTime) override;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "MainViewWidget")
	void OnIdleOver();
	UFUNCTION(BlueprintCallable, Category = "MainViewWidget")
	void ReInit();
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainViewWidget")
	class ULoopViewWidget* LoopView1;
};
