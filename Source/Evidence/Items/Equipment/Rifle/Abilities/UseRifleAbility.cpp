// Fill out your copyright notice in the Description page of Project Settings.


#include "UseRifleAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment/Rifle/Rifle.h"
#include "Evidence/Items/TrueProjectile.h"
#include "Evidence/Items/CosmeticProjectile.h"

UUseRifleAbility::UUseRifleAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Equipment.Gun.Cooldown.Rifle")));
}

void UUseRifleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Use rifle");

	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(GetCurrentActorInfo()->AvatarActor);

	FTransform SpawnTransform;

	if (ActorInfo->IsNetAuthority())
	{
		//True projectile

		ATrueProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATrueProjectile>(TrueProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->FinishSpawning(SpawnTransform);
	}
	else if (ActorInfo->IsLocallyControlled())
	{
		//Cosmetic projectile

		ACosmeticProjectile* Projectile = GetWorld()->SpawnActorDeferred<ACosmeticProjectile>(CosmeticProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->FinishSpawning(SpawnTransform);
	}
}

bool UUseRifleAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ARifle* Rifle = Cast<ARifle>(GetSourceObject(Handle, ActorInfo));
	if (!Rifle)
	{
		return false;
	}

	return Rifle->GetCurrentClip() >= 1;
}

void UUseRifleAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	ARifle* Rifle = Cast<ARifle>(GetSourceObject(Handle, ActorInfo));
	if (!Rifle)
	{
		return;
	}

	Rifle->SetCurrentClip(Rifle->GetCurrentClip() - 1);
}
