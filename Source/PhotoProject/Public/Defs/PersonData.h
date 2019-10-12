// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PersonData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PHOTOPROJECT_API UPersonData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "PersonData")
	class UTexture2D* m_pHeadThumbnail;
	UPROPERTY(BlueprintReadWrite, Category = "PersonData")
	class UTexture2D* m_pPhoto;
	UPROPERTY(BlueprintReadWrite, Category = "PersonData")
	FString m_strLocalVideoPath;
};