// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "CrouchAbility.generated.h"

/*
	Ability that toggles character crouch state
*/
UCLASS()
class ABILITYINPUTSYSTEM_API UCrouchAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UCrouchAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
