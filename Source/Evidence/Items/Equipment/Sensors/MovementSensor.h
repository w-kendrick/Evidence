// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "Evidence/Delegates.h"
#include "MovementSensor.generated.h"

UCLASS()
class EVIDENCE_API AMovementSensor : public APowerEquipment
{
	GENERATED_BODY()

public:
	AMovementSensor();

	FOnMovementSense OnMovementSense;

protected:
	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;

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
