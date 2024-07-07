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
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

protected:
	virtual void NativeConstruct() override;
	void ShowInteractPrompt(const float Duration, const FString DisplayString);
	void HideInteractPrompt();

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

	void SetInteractPromptVisibility(bool bVisibility, float Duration, FString DisplayString);
	void OnInventoryRequest();

	UPROPERTY(meta = (BindWidget))
	UTerminalMenu* TerminalMenu;

	UPROPERTY(meta = (BindWidget))
	UAttachmentBenchWidget* AttachmentWidget;

	void SetTerminalMenuVisibility(bool bVisibility);
	void SetAttachmentVisibility(bool bVisibility);

private:
	UFUNCTION()
	void SetupDelegates(APawn* OldPawn, APawn* NewPawn);
};
