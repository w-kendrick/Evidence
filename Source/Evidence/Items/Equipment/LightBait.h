// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "LightBait.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UPointLightComponent;

UCLASS()
class EVIDENCE_API ALightBait : public APowerEquipment
{
	GENERATED_BODY()

public:
	ALightBait();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* Stimulus;

	UPROPERTY(VisibleDefaultsOnly)
	UPointLightComponent* LightComponent;

	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;

	UPROPERTY(EditDefaultsOnly)
	float EventDelay;

private:
	FTimerHandle StrobeHandle;

	void StrobeEvent();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSynchronise(const bool State);
	
};
