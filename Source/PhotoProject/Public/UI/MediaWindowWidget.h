// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaWindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOPROJECT_API UMediaWindowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MediaWindowWidget")
	class UCanvasPanel* WindowPanel;
private:
	uint32 m_CurrentHolder = 99999;
	FVector2D m_StartPosition;
	FVector2D m_StartSlotPosition;

};
