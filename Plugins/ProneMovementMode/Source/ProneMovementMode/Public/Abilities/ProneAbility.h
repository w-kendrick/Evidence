// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "ProneAbility.generated.h"

/*
	Ability that toggles character prone state
*/
UCLASS()
class PRONEMOVEMENTMODE_API UProneAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UProneAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
