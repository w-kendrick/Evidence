// Fill out your copyright notice in the Description page of Project Settings.


#include "EIDropAbility.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

UEIDropAbility::UEIDropAbility()
{
	AbilityInputID = EAbilityInputID::Drop;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Drop"))));
}

void UEIDropAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}

		ABaseCharacter* const Char = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());

		if (!Char)
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
			return;
		}

		UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();

		if (!InventoryComponent)
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
			return;
		}

		InventoryComponent->DropEquipped();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UEIDropAbility::Activate()
{
	ABaseCharacter* const Char = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());

	if (!Char)
	{
		return;
	}

	UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();

	if (!InventoryComponent)
	{
		return;
	}

	InventoryComponent->DropEquipped();
}
