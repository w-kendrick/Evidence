// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "CharacterTest.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ACharacterTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	bool IsReady_Implementation() override;
	void StartTest() override;

protected:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	ABaseCharacter* BaseCharacter;

	void InjectInput(const UInputAction* Action, FVector Value);
	
};
