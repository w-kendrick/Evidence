// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "Evidence/Delegates.h"
#include "MovementSensor.generated.h"

UCLASS()
class EVIDENCE_API AMovementSensor : public AEquipment, public IPowerInterface
{
	GENERATED_BODY()

public:
	AMovementSensor();

	FOnMovementSense OnMovementSense;

	virtual UPowerComponent* GetPowerComponent() const override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UPowerComponent* PowerComponent;

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
