// Fill out your copyright notice in the Description page of Project Settings.


#include "RecordVideoAbility.h"
#include "Evidence/Items/Equipment/VideoCamera.h"

URecordVideoAbility::URecordVideoAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
}

void URecordVideoAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	AVideoCamera* const Camera = Cast<AVideoCamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	if (ActorInfo->IsNetAuthority())
	{
		if (Camera->GetIsRecording())
		{
			Camera->StopRecording();
		}
		else
		{
			Camera->StartRecording();
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool URecordVideoAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const AVideoCamera* const Camera = Cast<AVideoCamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		return false;
	}

	return Camera->hasCapturesRemaining();
}
