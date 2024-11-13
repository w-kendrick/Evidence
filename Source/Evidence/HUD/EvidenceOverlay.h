// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EvidenceOverlay.generated.h"

class UTerminalMenu;
class ULockerWidget;
class UTextBlock;
class UProgressBar;
class UWidgetSwitcher;
class UCanvasPanel;
class UStaminaWidget;
class UAmmoWidget;
class UPowerWidget;
class UGunWidget;
class UPacketLossWidget;
class UInventoryHotbar;

UCLASS()
class EVIDENCE_API UEvidenceOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void ShowInteractPrompt(const float Duration, const FString DisplayString);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InteractCanvas;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* InteractSwitcher;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* InteractBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InstantInteractText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DurationInteractText;

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
	ULockerWidget* LockerWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NightText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CashText;

	UPROPERTY(meta = (BindWidget))
	UStaminaWidget* StaminaWidget;

	UPROPERTY(meta = (BindWidget))
	UAmmoWidget* AmmoWidget;

	UPROPERTY(meta = (BindWidget))
	UPowerWidget* PowerWidget;

	UPROPERTY(meta = (BindWidget))
	UGunWidget* GunWidget;

	UPROPERTY(meta = (BindWidget))
	UPacketLossWidget* PacketLossWidget;

	UPROPERTY(meta = (BindWidget))
	UInventoryHotbar* InventoryHotbar;

private:
	void OnNightChanged(uint32 Night);
	void OnCashChanged(float Cash);

	void SetTerminalMenuVisibility(bool bVisibility);
	void SetLockerWidgetVisibility(bool bVisibility);
	void SetInteractPromptVisibility(bool bVisibility, float Duration, FString DisplayString);
	void SetInteractTimerState(bool bState, float Duration);

	void SetCoreWidgetVisibility(const bool bVisibility);
};
