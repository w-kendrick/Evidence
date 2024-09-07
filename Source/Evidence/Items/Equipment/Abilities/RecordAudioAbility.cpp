// Fill out your copyright notice in the Description page of Project Settings.


#include "RecordAudioAbility.h"
#include "Evidence/Items/Equipment/AudioRecorder.h"

URecordAudioAbility::URecordAudioAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void URecordAudioAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	AAudioRecorder* const Recorder = Cast<AAudioRecorder>(GetSourceObject(Handle, ActorInfo));

	if (!Recorder)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	if (ActorInfo->IsNetAuthority())
	{
		if (Recorder->GetIsRecording())
		{
			Recorder->StopRecording();
		}
		else
		{
			Recorder->StartRecording();
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool URecordAudioAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const AAudioRecorder* const Recorder = Cast<AAudioRecorder>(GetSourceObject(Handle, ActorInfo));

	if (!Recorder)
	{
		return false;
	}

	return Recorder->hasCapturesRemaining();
}
