// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePowerAbility.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"

UTogglePowerAbility::UTogglePowerAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
}

void UTogglePowerAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Toggle power");

	APoweredEquipment* Powered = Cast<APoweredEquipment>(GetSourceObject(Handle, ActorInfo));

	if (!Powered)
	{
		return;
	}

	Powered->ToggleActivation();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UTogglePowerAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	APoweredEquipment* Powered = Cast<APoweredEquipment>(GetSourceObject(Handle, ActorInfo));

	if (!Powered)
	{
		return false;
	}

	return Powered->GetPower() > 0;
}
