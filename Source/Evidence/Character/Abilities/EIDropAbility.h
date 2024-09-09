// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "EIDropAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEIDropAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UEIDropAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void Activate();
};
