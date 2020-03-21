// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoopViewWidget.generated.h"
DECLARE_STATS_GROUP(TEXT("MyGameProfiler"), STATGROUP_MyGameProfiler, STATCAT_Advanced);
DECLARE_CYCLE_STAT_EXTERN(TEXT("LoopViewWidget_UpdateLoop"), STAT_LoopViewWidget_UpdateLoop, STATGROUP_MyGameProfiler, );
/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API ULoopViewWidget : public UUserWidget
{
	struct FLoopAnimationData
	{
	public:
		bool IsPlaying() 
		{
			return m_bIsLooping;
		}
		bool IsPause()
		{
			return m_bIsLooping;
		}
		void Play()
		{
			m_bIsLooping = true;
			m_bIsPause = false;
		}
		void Pause()
		{
			m_bIsLooping = false;
			m_bIsPause = true;
		}
		void Stop()
		{
			m_bIsLooping = false;
			m_bIsPause = true;
		}
		bool m_bIsLooping;
		bool m_bIsPause;
		float m_fAnimateSpeed;
	};
	GENERATED_BODY()
public:
	// LoopViewWidget Function
	UFUNCTION(BlueprintCallable,Category = "LoopViewWidget")
	void InitData(const TArray<UObject*>& dataArray);
	// LoopViewWidget Function End

	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& InGeometry, float fDeltaTime) override;

	// LoopViewWidget Animation
	UFUNCTION(BlueprintCallable, Category = "LoopViewWidget")
	void BeginLoop(float fSpeed);
	UFUNCTION(BlueprintCallable, Category = "LoopViewWidget")
	void PauseLoop();
	void UpdateLoop(float fDeltaTime);
	UFUNCTION(BlueprintCallable, Category = "LoopViewWidget")
	void EndLoop();
	// LoopViewWidget Animation End
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "LoopViewWidget")
	void HandleItemClicked(class ULoopViewItemWidget* pItem);

private:

	void InitChildrenItems();
	void FilllMatrix();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LoopViewWidget")
	int32 m_nColumnNum;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LoopViewWidget")
	FVector2D m_ChildSize;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "LoopViewWidget")
		class UCanvasPanel* ContainerPanel;
	UPROPERTY(EditDefaultsOnly, Category = "LoopViewWidget")
		TSubclassOf<class ULoopViewItemWidget> ChildWidgetClass;

private:
	UPROPERTY()
	TArray<UObject*> m_DataArray;
	class ULoopViewItemWidget* CreateChild(int32 nRow, int32 nCol);
	FVector2D m_ContainerSize;
	int32 m_ContainerChildNum;
	FLoopAnimationData m_LoopAnimationData;
	TArray<TArray<int32>> m_NodeMatrix;
	int32 m_nCurrentDataIndex = 0;
};
