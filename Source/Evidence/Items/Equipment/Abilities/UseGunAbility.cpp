// Fill out your copyright notice in the Description page of Project Settings.


#include "UseGunAbility.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment/Gun.h"
#include "Evidence/Items/TrueProjectile.h"
#include "Evidence/Items/CosmeticProjectile.h"
#include "Kismet/KismetMathLibrary.h"

UUseGunAbility::UUseGunAbility()
{
	AbilityInputID = EAbilityInputID::Use;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Equipment.Gun.Cooldown.Rifle")));

	MaxRange = 2500.f;
	Damage = 70.f;
}

void UUseGunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Use gun");

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

	const FVector Start = Gun->GetWorldMesh()->GetSocketLocation(FName("Muzzle"));
	const FVector Target = Char->GetTraceStart() + Char->GetTraceDirection() * MaxRange;
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	const FTransform SpawnTransform = FTransform(Rotation, Start, FVector::OneVector);

	if (ActorInfo->IsNetAuthority())
	{
		//True projectile

		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel());

		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

		ATrueProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATrueProjectile>(TrueProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectHandle = DamageEffectSpecHandle;
		Projectile->FinishSpawning(SpawnTransform);
	}
	else if (ActorInfo->IsLocallyControlled())
	{
		//Cosmetic projectile

		ACosmeticProjectile* Projectile = GetWorld()->SpawnActorDeferred<ACosmeticProjectile>(CosmeticProjectileClass, SpawnTransform, nullptr, Char, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->FinishSpawning(SpawnTransform);
	}
}

bool UUseGunAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	AGun* Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return false;
	}

	return Gun->GetCurrentClip() >= 1;
}

void UUseGunAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	AGun* Gun = Cast<AGun>(GetSourceObject(Handle, ActorInfo));
	if (!Gun)
	{
		return;
	}

	Gun->SetCurrentClip(Gun->GetCurrentClip() - 1);
}
