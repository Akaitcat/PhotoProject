// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"
#include "Engine.h"
#include "CoreUObject.h"
#include "PersonData.h"

TSharedPtr<FDataManager> FDataManager::ms_pInstance = nullptr;

FDataManager& FDataManager::GetInstance()
{
	if (!ms_pInstance.IsValid()) {
		ms_pInstance = MakeShareable(new FDataManager());
	}
	return *ms_pInstance;
}

FDataManager::FDataManager()
{

}

TArray<UObject*> FDataManager::GetTestData()
{
	TArray<UObject*> testDataArray;
	FString strTextureSoftPath;
	for (int32 i = 0; i < 990;i++) {
		UPersonData* newData = NewObject<UPersonData>();
		strTextureSoftPath = FString::Printf(TEXT("'/Game/PhotoProject/Textures/Test/%04d.%04d'"),i,i);
		newData->m_pHeadThumbnail = LoadObject<UTexture2D>(nullptr, *strTextureSoftPath);
		newData->m_strLocalVideoPath = TEXT("http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4");
		newData->m_pPhoto = newData->m_pHeadThumbnail;
		testDataArray.Add(newData);
	}
	return testDataArray;
}
