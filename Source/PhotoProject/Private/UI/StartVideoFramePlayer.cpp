
#include "StartVideoFramePlayer.h"
#include "DataManager.h"
#include "UserSetting.h"


void UStartVideoFramePlayer::NativeConstruct()
{
	Super::NativeConstruct();
	Stop();
	m_Frames = FDataManager::GetInstance().LoadStartVideoFrames();
}

void UStartVideoFramePlayer::NativeTick(const FGeometry& InGeometry, float fDeltaTime)
{
	Super::NativeTick(InGeometry, fDeltaTime);
	if (m_bIsPlaying) {
		if (m_fCurrentTime > (m_nCurrentIndex + 1) * UUserSetting::GetUserSetting()->m_fStartVideoFrameTime) {
			m_nCurrentIndex++;
			if (m_nCurrentIndex>= m_Frames.Num()) {
				Stop();
				OnVideoReachEnd.ExecuteIfBound();
			}
			else {
				VideoImage->SetBrushFromTexture(m_Frames[m_nCurrentIndex]);
			}
		}
		m_fCurrentTime += fDeltaTime;
	}
}

void UStartVideoFramePlayer::Play()
{
	m_bIsPlaying = true;
	m_nCurrentIndex = 0;
	m_fCurrentTime = 0;
	if (m_Frames.Num() > 0) {
		VideoImage->SetBrushFromTexture(m_Frames[0]);
	}
}

void UStartVideoFramePlayer::Stop()
{
	m_bIsPlaying = false;
	m_nCurrentIndex = 0;
	m_fCurrentTime = 0;
}
