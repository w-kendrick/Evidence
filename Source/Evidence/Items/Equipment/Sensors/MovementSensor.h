// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"
#include "MovementSensor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMovementSense)

UCLASS()
class EVIDENCE_API AMovementSensor : public APoweredEquipment
{
	GENERATED_BODY()

public:
	AMovementSensor();

	FOnMovementSense OnMovementSense;

protected:
	virtual void Activate() override;
	virtual void Deactivate() override;

	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY()
	TArray<FVector> PreviousSense;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;

	UPROPERTY(EditDefaultsOnly)
	float SenseRadius;

private:
	bool doArraysMatch(const TArray<FVector>& Arr1, const TArray<FVector>& Arr2) const;
	
};
