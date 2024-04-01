// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueProjectile.h"
#include "Components/SphereComponent.h"
#include "Evidence/Interfaces/Damageable.h"

ATrueProjectile::ATrueProjectile()
{
	bReplicates = true;
}

void ATrueProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstigator() && GetInstigator()->IsLocallyControlled())
	{
		Sphere->SetVisibility(false, true);
	}
}

void ATrueProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDamageable* Damageable = Cast<IDamageable>(OtherActor);

	if (Damageable)
	{
		Damageable->ReceiveDamage(30.f);
	}
}
