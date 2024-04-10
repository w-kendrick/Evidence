// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadGunAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

UReloadGunAbility::UReloadGunAbility()
{
	AbilityInputID = EAbilityInputID::Reload;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Reload")));
}

void UReloadGunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(GetCurrentActorInfo()->AvatarActor);
	if (!Char)
	{
		return;
	}

	UInventoryComponent* InventoryComp = Char->GetInventoryComponent();
	if (!InventoryComp)
	{
		return;
	}

	const TArray<uint8> AvailableAmmo = InventoryComp->FindAmmunitionOfType(AmmoClass);
}

bool UReloadGunAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return false;
}
