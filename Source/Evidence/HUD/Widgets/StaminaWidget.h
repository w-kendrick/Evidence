// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

UCLASS()
class EVIDENCE_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class AEvidenceCharacter* Char;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StaminaText;

	void OnStaminaChanged(float NewStamina);

private:
	FTimerHandle SetupHandle;
	void ReattemptSetup();
	
};
