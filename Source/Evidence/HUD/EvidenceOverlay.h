// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EvidenceOverlay.generated.h"

class UTerminalMenu;
class UAttachmentBenchWidget;

UCLASS()
class EVIDENCE_API UEvidenceOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	void ShowInteractPrompt(const float Duration, const FString DisplayString);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* InteractCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* InteractSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* InteractBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InstantInteractText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DurationInteractText;

	float CurrentInteractionTime;
	float InteractionDuration;

	UPROPERTY(EditDefaultsOnly)
	float InteractionTick = 0.01f;

	FTimerHandle InteractionTimer;

	void InteractionProgressTick();

	bool bInventoryWidgetVisible = false;

	UPROPERTY(meta = (BindWidget))
	UTerminalMenu* TerminalMenu;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NightText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CashText;

	void OnNightChanged(uint32 Night);
	void OnCashChanged(float Cash);

	void SetTerminalMenuVisibility(bool bVisibility);
	void SetInteractPromptVisibility(bool bVisibility, float Duration, FString DisplayString);
	void SetInteractTimerState(bool bState, float Duration);
};
