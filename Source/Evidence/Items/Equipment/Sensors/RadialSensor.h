// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "Evidence/Delegates.h"
#include "RadialSensor.generated.h"

UCLASS()
class EVIDENCE_API ARadialSensor : public AEquipment, public IPowerInterface
{
	GENERATED_BODY()

public:
	ARadialSensor();

	FOnRadialSense OnRadialSense;

	virtual UPowerComponent* GetPowerComponent() const override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UPowerComponent* PowerComponent;

	virtual void Activate() override;
	virtual void Deactivate() override;

	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;

	UPROPERTY(EditDefaultsOnly)
	float SenseRadius;
	
};
