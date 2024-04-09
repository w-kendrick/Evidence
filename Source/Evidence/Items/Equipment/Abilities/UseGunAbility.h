// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/Abilities/EIGameplayAbility.h"
#include "UseGunAbility.generated.h"

class ATrueProjectile;
class ACosmeticProjectile;

UCLASS()
class EVIDENCE_API UUseGunAbility : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UUseGunAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATrueProjectile> TrueProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACosmeticProjectile> CosmeticProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;

};
