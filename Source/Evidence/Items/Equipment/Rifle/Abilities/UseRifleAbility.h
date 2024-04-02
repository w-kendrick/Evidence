// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/Abilities/EIGameplayAbility.h"
#include "UseRifleAbility.generated.h"

class ATrueProjectile;
class ACosmeticProjectile;

UCLASS()
class EVIDENCE_API UUseRifleAbility : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UUseRifleAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATrueProjectile> TrueProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACosmeticProjectile> CosmeticProjectileClass;

};
