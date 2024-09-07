// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AdvancedGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

/**
 * 
 */
UCLASS()
class ABILITYINPUTSYSTEM_API UAdvancedGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	EAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EAbilityActivationPolicy ActivationPolicy;

	UFUNCTION(BlueprintCallable)
	void CancelAbilityWithTags(const FGameplayTagContainer Tags);
	
};
