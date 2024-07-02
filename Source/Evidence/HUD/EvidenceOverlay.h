// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EvidenceOverlay.generated.h"

class UInventoryWidget;
class UTerminalMenu;
class UAttachmentBenchWidget;

UCLASS()
class EVIDENCE_API UEvidenceOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowInteractPrompt(const float Duration);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	void ShowTerminalMenu();
	void HideTerminalMenu();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* InteractCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* InteractSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* InteractBar;

	float CurrentInteractionTime;
	float InteractionDuration;

	UPROPERTY(EditDefaultsOnly)
	float InteractionTick = 0.01f;

	FTimerHandle InteractionTimer;

	void InteractionProgressTick();

	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;

	bool bInventoryWidgetVisible = false;

	void OnInventoryRequest();

	UPROPERTY(meta = (BindWidget))
	UTerminalMenu* TerminalMenu;

	UPROPERTY(meta = (BindWidget))
	UAttachmentBenchWidget* AttachmentWidget;

	UFUNCTION()
	void SetAttachmentVisibility(bool bVisibility);

private:
	FTimerHandle SetupHandle;
	void ReattemptSetup();
};
