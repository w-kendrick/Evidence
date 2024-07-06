// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleAttachmentPowerAbility.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"

UToggleAttachmentPowerAbility::UToggleAttachmentPowerAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
}

void UToggleAttachmentPowerAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	IPowerInterface* const Powered = Cast<IPowerInterface>(GetAttachment(Handle, ActorInfo));

	if (!Powered)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Toggle power");
	Powered->GetPowerComponent()->ToggleActivation();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UToggleAttachmentPowerAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const IPowerInterface* const Powered = Cast<IPowerInterface>(GetAttachment(Handle, ActorInfo));

	if (!Powered)
	{
		return false;
	}

	return Powered->GetPowerComponent()->GetPower() > 0;
}
