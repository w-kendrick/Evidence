// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueProjectile.h"
#include "Components/SphereComponent.h"
#include "Evidence/Interfaces/Damageable.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

ATrueProjectile::ATrueProjectile()
{
	bReplicates = true;
}

void ATrueProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstigator() && GetInstigator()->IsLocallyControlled() && !GetInstigator()->HasAuthority())
	{
		Sphere->SetVisibility(false, true);
	}
}

void ATrueProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const IAbilitySystemInterface* const AS = Cast<IAbilitySystemInterface>(OtherActor);

	if (AS)
	{
		UAbilitySystemComponent* const ASC = AS->GetAbilitySystemComponent();

		if (ASC)
		{
			ASC->ApplyGameplayEffectSpecToSelf(*DamageEffectHandle.Data);
		}
	}

	IDamageable* const Damageable = Cast<IDamageable>(OtherActor);

	if (Damageable)
	{
		Damageable->ReceiveDamage(30.f);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + 250 * FVector::UpVector, FColor::Purple, true, -1.0f, 0, 5);

	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
