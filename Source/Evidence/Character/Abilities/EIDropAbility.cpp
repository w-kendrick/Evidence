// Fill out your copyright notice in the Description page of Project Settings.


#include "EIDropAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"

UEIDropAbility::UEIDropAbility()
{
	AbilityInputID = EAbilityInputID::Drop;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Drop")));
}

void UEIDropAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}

		AEvidenceCharacter* const Character = CastChecked<AEvidenceCharacter>(ActorInfo->AvatarActor.Get());
		Character->Drop();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
