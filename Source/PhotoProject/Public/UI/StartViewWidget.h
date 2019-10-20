// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UStartViewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
