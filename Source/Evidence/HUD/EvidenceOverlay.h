// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EvidenceOverlay.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowInteractPrompt(const float Duration);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* InteractCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* InteractSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* InteractBar;

	float CurrentInteractionTime;
	float InteractionDuration;

	UPROPERTY(EditDefaultsOnly)
	float InteractionTick;

	FTimerHandle InteractionTimer;

	void InteractionProgressTick();
	
};
