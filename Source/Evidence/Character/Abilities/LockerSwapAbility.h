// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "LockerSwapAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ULockerSwapAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
	
};
