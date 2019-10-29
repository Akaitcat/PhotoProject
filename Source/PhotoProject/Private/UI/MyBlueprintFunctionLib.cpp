// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyBlueprintFunctionLib.h"
#include "Defs/PersonData.h"
#include "Framework/DataManager.h"
#include "StartViewWidget.generated.h"

TArray<UPersonData*> UMyBlueprintFunctionLib::GetDatasByNameFilters(FString strNameShort)
{
	TArray<UPersonData*> result;
	TSet<UObject*> dataSet;
	dataSet.Append(FDataManager::GetInstance().GetData(TEXT("2006")));
	dataSet.Append(FDataManager::GetInstance().GetData(TEXT("2011")));
	dataSet.Append(FDataManager::GetInstance().GetData(TEXT("2016")));
	dataSet.Append(FDataManager::GetInstance().GetData(TEXT("2020")));
	for (auto data : dataSet)
	{
		UPersonData* personData = Cast<UPersonData>(data);
		if (personData) {
			if (personData->m_strSearchKey.Contains(strNameShort,ESearchCase::IgnoreCase)) {
				result.Add(personData);
			}
		}
	}
	return result;
}
