// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceTripodAbility.h"
#include "Evidence/Items/Equipment/Tripod.h"
#include "AbilitySystemBlueprintLibrary.h"

UPlaceTripodAbility::UPlaceTripodAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void UPlaceTripodAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	ATripod* const Tripod = Cast<ATripod>(GetSourceObject(Handle, ActorInfo));

	if (!Tripod)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();

	FGameplayAbilityTargetDataHandle DropHandle;
	DropHandle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = DropHandle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorInfo->AvatarActor.Get(), FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Drop"))), Payload);

	Tripod->Plant();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UPlaceTripodAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return CanPlantHere();
}

bool UPlaceTripodAbility::CanPlantHere() const
{
	return true;
}
