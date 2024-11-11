// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpectatorOverlay.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class EVIDENCE_API USpectatorOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

private:
	void OnSpectateeChanged(APawn* Pawn);
	
};
