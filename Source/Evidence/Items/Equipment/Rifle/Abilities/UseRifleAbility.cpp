// Fill out your copyright notice in the Description page of Project Settings.


#include "UseRifleAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"

UUseRifleAbility::UUseRifleAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Equipment.Gun.Cooldown.Rifle")));
}

void UUseRifleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Use rifle");
}

bool UUseRifleAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}