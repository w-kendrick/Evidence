// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCycleDownAbility.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

UInventoryCycleDownAbility::UInventoryCycleDownAbility()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag("Ability.CycleInventory.Down"));
}

void UInventoryCycleDownAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

	InventoryComponent->DecrementSelectedIndex();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}