// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EvidenceHUD.generated.h"

class UEvidenceOverlay;
class USpectatorOverlay;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AEvidenceHUD : public AHUD
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEvidenceOverlay> EvidenceOverlayClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USpectatorOverlay> SpectatorOverlayClass;

	UPROPERTY()
	UEvidenceOverlay* Overlay;

	UPROPERTY()
	USpectatorOverlay* SpectatorOverlay;

public:
	void AddEvidenceOverlay();
	void AddSpectatorOverlay();

private:
	void OnSpectatingChanged(bool bIsSpectating);
	
};
