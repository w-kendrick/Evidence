// Fill out your copyright notice in the Description page of Project Settings.


#include "EIDropAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

UEIDropAbility::UEIDropAbility()
{
	AbilityInputID = EAbilityInputID::Drop;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
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

		AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetAvatarActorFromActorInfo());

		if (!Char)
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
			return;
		}

		UInventoryComponent* const InventoryComponent = Char->GetInventoryComponent();

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
	AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetAvatarActorFromActorInfo());

	if (!Char)
	{
		return;
	}

	UInventoryComponent* const InventoryComponent = Char->GetInventoryComponent();

	if (!InventoryComponent)
	{
		return;
	}

	InventoryComponent->DropEquipped();
}
