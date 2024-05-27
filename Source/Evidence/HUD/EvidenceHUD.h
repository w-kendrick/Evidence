// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EvidenceHUD.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AEvidenceHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEvidenceOverlay> OverlayClass;

	UPROPERTY()
	UEvidenceOverlay* Overlay;

public:
	UEvidenceOverlay* GetOverlay() const;
	void AddOverlay();

	void ShowInteractPrompt(const float Duration);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	void ShowTerminalMenu();
	void HideTerminalMenu();
	
};
