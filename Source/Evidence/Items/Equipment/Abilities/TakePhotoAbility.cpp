// Fill out your copyright notice in the Description page of Project Settings.


#include "TakePhotoAbility.h"
#include "Evidence/Items/Equipment/Camera.h"

UTakePhotoAbility::UTakePhotoAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
}

void UTakePhotoAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	ACamera* Camera = Cast<ACamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	if (ActorInfo->IsLocallyControlled())
	{
		Camera->TakePhoto();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UTakePhotoAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ACamera* Camera = Cast<ACamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		return false;
	}

	return Camera->GetRemainingPhotos() > 0;
}

void UTakePhotoAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	ACamera* Camera = Cast<ACamera>(GetSourceObject(Handle, ActorInfo));

	if (!Camera)
	{
		return;
	}

	Camera->SetRemainingPhotos(Camera->GetRemainingPhotos() - 1);
}
