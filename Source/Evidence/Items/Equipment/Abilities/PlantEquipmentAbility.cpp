// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantEquipmentAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment/PlantableEquipment.h"
#include "AbilitySystemBlueprintLibrary.h"

UPlantEquipmentAbility::UPlantEquipmentAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void UPlantEquipmentAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	APlantableEquipment* const Plantable = Cast<APlantableEquipment>(GetSourceObject(Handle, ActorInfo));
	if (!Plantable)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorInfo->AvatarActor.Get(), FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Drop"))), Payload);

	Plantable->Plant();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UPlantEquipmentAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	APlantableEquipment* const Plantable = Cast<APlantableEquipment>(GetSourceObject(Handle, ActorInfo));
	if (!Plantable)
	{
		return false;
	}

	return Plantable->CanPlant();
}

void UPlantEquipmentAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetCurrentActorInfo()->AvatarActor);
	if (!Char)
	{
		return;
	}

	Char->Drop();
}
