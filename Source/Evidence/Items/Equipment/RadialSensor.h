// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"
#include "RadialSensor.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRadialSense, ARadialSensor*, const TArray<FVector>)

UCLASS()
class EVIDENCE_API ARadialSensor : public APoweredEquipment
{
	GENERATED_BODY()

public:
	ARadialSensor();

	FOnRadialSense OnRadialSense;

protected:
	virtual void Activate() override;
	virtual void Deactivate() override;

	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;

	UPROPERTY(EditDefaultsOnly)
	float SenseRadius;
	
};
