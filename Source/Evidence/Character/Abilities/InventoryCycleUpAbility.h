// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "InventoryCycleUpAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UInventoryCycleUpAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UInventoryCycleUpAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
};
