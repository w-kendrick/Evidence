// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapPlayerWidget.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UMapPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ABaseCharacter* GetCharacter() const { return Character; }
	void SetCharacter(ABaseCharacter* const Char) { Character = Char; }

private:
	UPROPERTY()
	ABaseCharacter* Character;
};
