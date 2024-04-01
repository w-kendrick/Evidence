// Fill out your copyright notice in the Description page of Project Settings.


#include "UseRifleAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment/Rifle/Rifle.h"

UUseRifleAbility::UUseRifleAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Equipment.Gun.Cooldown.Rifle")));
}

void UUseRifleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Use rifle");

	if (ActorInfo->IsNetAuthority())
	{
		//True projectile
	}
	else if (ActorInfo->IsLocallyControlled())
	{
		//Cosmetic only projectile
	}
}

bool UUseRifleAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ARifle* Rifle = Cast<ARifle>(GetSourceObject(Handle, ActorInfo));
	if (!Rifle)
	{
		return false;
	}

	return Rifle->GetCurrentClip() >= 1;
}

void UUseRifleAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	ARifle* Rifle = Cast<ARifle>(GetSourceObject(Handle, ActorInfo));
	if (!Rifle)
	{
		return;
	}

	Rifle->SetCurrentClip(Rifle->GetCurrentClip() - 1);
}
