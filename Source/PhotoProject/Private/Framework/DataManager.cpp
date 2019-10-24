// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"
#include "Engine.h"
#include "CoreUObject.h"
#include "ImageUtils.h"
#include "Defs/PersonData.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "windows.h"
#include "Windows/HideWindowsPlatformTypes.h"


bool FMyDirectoryVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	if (bIsDirectory) {
		m_DirectoryPaths.Add(FilenameOrDirectory);
	}
	else {
		m_FilePaths.Add(FilenameOrDirectory);
	}
	return true;
}

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
	LoadData(TEXT("2016"));
	return testDataArray;
}

TArray<UObject*> FDataManager::GetData(const FString& strYear)
{
	if (TArray<UObject*>* result = m_DataMap.Find(strYear)) {
		return *result;
	}
	else {
		return {};
	}
}

void FDataManager::LoadAllData()
{
	m_DataMap.Add(TEXT("2006"), LoadData(TEXT("2006")));
	m_DataMap.Add(TEXT("2011"), LoadData(TEXT("2011")));
	m_DataMap.Add(TEXT("2016"), LoadData(TEXT("2016")));
	m_DataMap.Add(TEXT("2020"), LoadData(TEXT("2020")));
}

TArray<UObject*> FDataManager::LoadData(const TCHAR* szYear)
{
	TArray<UObject*> personDataArray;
	FString strRootDir = FPaths::ProjectDir().Append(TEXT("Root/"));
	strRootDir.Append(szYear);
	TArray<FString> directoriesToSkip;
	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	FMyDirectoryVisitor myVisitor;
	if (platformFile.IterateDirectory(*strRootDir, myVisitor)) {
		for(const FString& strDirectory:myVisitor.m_DirectoryPaths) {
			FMyDirectoryVisitor personVisitor;
			UPersonData* newData = NewObject<UPersonData>();
			newData->m_strDirectoryName = strDirectory;
			FString strDiectoryName;
			strDirectory.Split(TEXT("/"), nullptr, &strDiectoryName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			strDiectoryName.Split(TEXT("_"), &newData->m_strIndex, &newData->m_strName);
			newData->m_strName.Split(TEXT("_"), &newData->m_strName, &newData->m_strSearchKey);
			if (platformFile.IterateDirectory(*strDirectory, personVisitor))
			{
				for (const FString& strFilePath : personVisitor.m_FilePaths) {
					FString strFileName;
					strFilePath.Split(TEXT("/"), nullptr, &strFileName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
					if (strFileName.EndsWith(TEXT(".txt"), ESearchCase::IgnoreCase)) {
						TArray<uint8> buffer;
						FFileHelper::LoadFileToArray(buffer, *strFilePath);
						buffer.AddZeroed(1);
						UE_LOG(LogTemp,Log,TEXT("strDiectoryName:%s"), *newData->m_strIndex);
						newData->m_strDescription = GB2312_TO_UTF8(buffer);
					}
					else if (strFileName.EndsWith(TEXT(".jpg"), ESearchCase::IgnoreCase)
						|| strFileName.EndsWith(TEXT(".jpeg"), ESearchCase::IgnoreCase)) {
						if (strFileName.Contains(TEXT("small"))) {
							newData->m_pHeadThumbnail = FImageUtils::ImportFileAsTexture2D(strFilePath);
						}
						else {
							newData->m_strLocalPhotoPath = strFilePath;
							//newData->m_pPhoto = FImageUtils::ImportFileAsTexture2D(strFilePath);
						}
					}
					else if (strFileName.EndsWith(TEXT(".mp4"), ESearchCase::IgnoreCase)) {
						newData->m_strLocalVideoPath = strFilePath;
					}
				}
			}
			personDataArray.Add(newData);
		}
	}
	return personDataArray;
}

FString FDataManager::GB2312_TO_UTF8(const TArray<uint8>& szGB2312)
{
	int32 nWCHARNum = MultiByteToWideChar(CP_ACP, 0, (const ANSICHAR*)szGB2312.GetData(), -1, NULL, 0);
	TCHAR* dstBuffer = new TCHAR[nWCHARNum+1];
	FPlatformMemory::Memzero(dstBuffer, sizeof(TCHAR)*(nWCHARNum + 1));
	nWCHARNum = MultiByteToWideChar(CP_ACP, 0, (const ANSICHAR*)szGB2312.GetData(), szGB2312.Num(), dstBuffer, nWCHARNum);
	FString strResult(dstBuffer);
	delete[] dstBuffer;
	return strResult;
}