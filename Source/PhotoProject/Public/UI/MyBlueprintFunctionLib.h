// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UMyBlueprintFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category = "MyBlueprintFunctionLib")
	static TArray<class UPersonData*> GetDatasByNameFilters(FString strNameShort);
};
