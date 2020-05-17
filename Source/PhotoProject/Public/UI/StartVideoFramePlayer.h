// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "StartVideoFramePlayer.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnVideoReachEnd);

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UStartVideoFramePlayer : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& InGeometry, float fDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="StartVideoFramePlayer")
	void Play();
	UFUNCTION(BlueprintCallable, Category = "StartVideoFramePlayer")
	void Stop();

protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget), Category = "StartVideoFramePlayer")
	UImage* VideoImage;
	UPROPERTY(EditAnywhere, meta=(IsBindableEvent = "True"), Category = "StartVideoFramePlayer")
	FOnVideoReachEnd OnVideoReachEnd;

private:

	UPROPERTY()
	TArray<UTexture2D*> m_Frames;
	int32 m_nCurrentIndex;
	float m_fCurrentTime;
	bool m_bIsPlaying;

};
