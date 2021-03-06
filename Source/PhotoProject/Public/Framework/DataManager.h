// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "GenericPlatform/GenericPlatformFile.h"
class FMyDirectoryVisitor
	: public IPlatformFile::FDirectoryVisitor
{
public:
	TArray<FString> m_DirectoryPaths;
	TArray<FString> m_FilePaths;
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};

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
	TArray<UObject*> GetData(const FString& strYear);
	TArray<UObject*> GetAllData();
	void LoadAllData();
	TArray<UTexture2D*> LoadStartVideoFrames();
	TArray<UTexture2D*> GetStartVideoFrames();
private:
	TArray<UObject*> LoadData(const TCHAR* szYear);
private:
	FString GB2312_TO_UTF8(const TArray<uint8>& strGB2312);
	TMap<FString, TArray<UObject*>> m_DataMap;
	TArray<UTexture2D*> m_StartVideoFrames;
};
