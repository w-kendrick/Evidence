// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/Abilities/EIGameplayAbility.h"
#include "ReloadGunAbility.generated.h"

class AAmmunition;

UCLASS()
class EVIDENCE_API UReloadGunAbility : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UReloadGunAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAmmunition> AmmoClass;
	
};
