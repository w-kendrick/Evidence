// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "Evidence/Delegates.h"
#include "RadialSensor.generated.h"

UCLASS()
class EVIDENCE_API ARadialSensor : public APowerEquipment
{
	GENERATED_BODY()

public:
	ARadialSensor();

	FOnRadialSense OnRadialSense;

protected:
	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;

	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;

	UPROPERTY(EditDefaultsOnly)
	float SenseRadius;
	
};
