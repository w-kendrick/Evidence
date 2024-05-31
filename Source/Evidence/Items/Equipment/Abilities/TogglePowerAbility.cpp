// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePowerAbility.h"
#include "Evidence/Interfaces/PowerInterface.h"

UTogglePowerAbility::UTogglePowerAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void UTogglePowerAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	IPowerInterface* const Powered = Cast<IPowerInterface>(GetSourceObject(Handle, ActorInfo));

	if (!Powered)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	Powered->GetPowerComponent()->ToggleActivation();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UTogglePowerAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const IPowerInterface* const Powered = Cast<IPowerInterface>(GetSourceObject(Handle, ActorInfo));

	if (!Powered)
	{
		return false;
	}

	return Powered->GetPowerComponent()->GetPower() > 0;
}
