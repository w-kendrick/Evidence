// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadGunAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment/Gun.h"
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

	AGun* Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return;
	}

	const uint8 Required = Gun->GetMaxClipSize() - Gun->GetCurrentClip();

	UInventoryComponent* InventoryComp = Char->GetInventoryComponent();
	if (!InventoryComp)
	{
		return;
	}

	const uint8 Available = InventoryComp->ConsumeAmmo(AmmoClass, Required);
}

bool UReloadGunAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	AGun* Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return false;
	}

	const uint8 Required = Gun->GetMaxClipSize() - Gun->GetCurrentClip();

	return Required > 0;
}
