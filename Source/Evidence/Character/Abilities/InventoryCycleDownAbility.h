// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "InventoryCycleDownAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UInventoryCycleDownAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UInventoryCycleDownAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
