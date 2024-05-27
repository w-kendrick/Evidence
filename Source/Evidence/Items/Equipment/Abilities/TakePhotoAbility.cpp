// Fill out your copyright notice in the Description page of Project Settings.


#include "TakePhotoAbility.h"
#include "Evidence/Items/Equipment/PhotoCamera.h"

UTakePhotoAbility::UTakePhotoAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void UTakePhotoAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	APhotoCamera* const Camera = Cast<APhotoCamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	if (ActorInfo->IsLocallyControlled())
	{
		Camera->TakePhoto();
	}

	if (ActorInfo->IsNetAuthority())
	{
		Camera->SaveFrame();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UTakePhotoAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const APhotoCamera* const Camera = Cast<APhotoCamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		return false;
	}

	return Camera->hasCapturesRemaining();
}
