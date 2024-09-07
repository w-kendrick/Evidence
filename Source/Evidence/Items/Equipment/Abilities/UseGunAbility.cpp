// Fill out your copyright notice in the Description page of Project Settings.


#include "UseGunAbility.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Items/Equipment/Gun.h"
#include "Evidence/Items/TrueProjectile.h"
#include "Evidence/Items/CosmeticProjectile.h"
#include "Kismet/KismetMathLibrary.h"

UUseGunAbility::UUseGunAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Use"))));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Equipment.Gun.Cooldown.Rifle"))));

	MaxRange = 2500.f;
	Damage = 70.f;
}

void UUseGunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	ABaseCharacter* const Char = Cast<ABaseCharacter>(GetCurrentActorInfo()->AvatarActor);
	if (!Char)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	const AGun* const Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	const FVector Start = Gun->GetWorldMesh()->GetSocketLocation(FName("Muzzle"));
	const FVector Target = Char->GetTraceStart() + Char->GetTraceDirection() * MaxRange;
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	const FTransform SpawnTransform = FTransform(Rotation, Start, FVector::OneVector);

	if (ActorInfo->IsNetAuthority())
	{
		//True projectile

		const FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel());

		ATrueProjectile* const Projectile = GetWorld()->SpawnActorDeferred<ATrueProjectile>(TrueProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectHandle = DamageEffectSpecHandle;
		Projectile->SetInstigator(Char);
		Projectile->FinishSpawning(SpawnTransform);
	}
	else if (ActorInfo->IsLocallyControlled())
	{
		//Cosmetic projectile

		ACosmeticProjectile* const Projectile = GetWorld()->SpawnActorDeferred<ACosmeticProjectile>(CosmeticProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->FinishSpawning(SpawnTransform);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UUseGunAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const AGun* const Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return false;
	}

	return Gun->GetCurrentClip() >= 1;
}

void UUseGunAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	AGun* const Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return;
	}

	Gun->SetCurrentClip(Gun->GetCurrentClip() - 1);
}
