// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"
#include "MovementSensor.generated.h"

UCLASS()
class EVIDENCE_API AMovementSensor : public APoweredEquipment
{
	GENERATED_BODY()

public:
	AMovementSensor();

protected:
	virtual void Activate() override;
	virtual void Deactivate() override;

	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;
	
};
