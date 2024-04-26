// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/TrueProjectile.h"
#include "TrueTrackerDart.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackDartBroadcast, const FVector&);

UCLASS()
class EVIDENCE_API ATrueTrackerDart : public ATrueProjectile
{
	GENERATED_BODY()

public:
	ATrueTrackerDart();

	FOnTrackDartBroadcast OnTrackDartBroadcast;

protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	void BroadcastLocation();

	FTimerHandle BroadcastHandle;

	UPROPERTY(EditDefaultsOnly)
	float BroadcastDelay;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxBroadcastCount;

private:
	uint8 CurrentBroadcastCount;
	
};
