// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameplayEffectTypes.h"
#include "TrueProjectile.generated.h"

UCLASS()
class EVIDENCE_API ATrueProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	ATrueProjectile();

	FGameplayEffectSpecHandle DamageEffectHandle;

protected:
	virtual void BeginPlay() override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
