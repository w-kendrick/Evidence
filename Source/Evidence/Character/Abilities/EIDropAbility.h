// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EIGameplayAbility.h"
#include "EIDropAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEIDropAbility : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UEIDropAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
