// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PHOTOPROJECT_API FDataManager
{
public:
	static FDataManager& GetInstance();
	static TSharedPtr<FDataManager> ms_pInstance;
private:
	FDataManager();
	FDataManager(const FDataManager&) {};
public:
	TArray<UObject*> GetTestData();
};
