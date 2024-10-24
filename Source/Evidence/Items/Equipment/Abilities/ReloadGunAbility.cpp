// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadGunAbility.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Items/Equipment/Gun.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

UReloadGunAbility::UReloadGunAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Reload"))));
}

void UReloadGunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	const ABaseCharacter* const Char = Cast<ABaseCharacter>(GetCurrentActorInfo()->AvatarActor);
	if (!Char)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	AGun* const Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	const uint8 Required = Gun->GetMaxClipSize() - Gun->GetCurrentClip();

	UInventoryManagerComponent* const InventoryComp = Char->GetInventoryComponent();
	if (!InventoryComp)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	const uint8 Available = InventoryComp->ConsumeAmmo(AmmoClass, Required);

	Gun->AddAmmoToClip(Available);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UReloadGunAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	const AGun* const Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return false;
	}

	const uint8 Required = Gun->GetMaxClipSize() - Gun->GetCurrentClip();

	const ABaseCharacter* const Char = Cast<ABaseCharacter>(GetCurrentActorInfo()->AvatarActor);
	if (!Char)
	{
		return false;
	}

	const UInventoryManagerComponent* const InventoryComp = Char->GetInventoryComponent();
	if (!InventoryComp)
	{
		return false;
	}

	return Required > 0 && InventoryComp->IsAmmoAvailable(AmmoClass);
}
