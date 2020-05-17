// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserSetting.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UUserSetting : public UObject
{
	GENERATED_BODY()
private:
	UUserSetting();
public:
	UFUNCTION(BlueprintPure, Category = "UserSetting")
	static UUserSetting* GetUserSetting();

private:
	void InitFromFile();
private:
	const FString mk_SettingPath = FPaths::ProjectDir() / TEXT("Configs/UserSetting.ini");
	static UUserSetting* ms_pSingle;
public:
	UPROPERTY(BlueprintReadWrite, Category = "UserSetting")
	int32 m_nIntroduceFontSize;
	UPROPERTY(BlueprintReadWrite, Category = "UserSetting")
	float m_fStartVideoFrameTime;
};
