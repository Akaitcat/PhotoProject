// Fill out your copyright notice in the Description page of Project Settings.


#include "UserSetting.h"
UUserSetting* UUserSetting::ms_pSingle = nullptr;
UUserSetting::UUserSetting():
	m_nIntroduceFontSize(10)
{
	InitFromFile();
}

UUserSetting* UUserSetting::GetUserSetting()
{
	if (!ms_pSingle) {
		ms_pSingle = NewObject<UUserSetting>();
		ms_pSingle->AddToRoot();
	}
	return ms_pSingle;
}

void UUserSetting::InitFromFile()
{
	if (GConfig) {
		GConfig->Flush(true, mk_SettingPath);
		GConfig->GetInt(TEXT("/Script/UserSetting.Appearance"),TEXT("IntroduceFontSize"), m_nIntroduceFontSize, mk_SettingPath);
	}
}
