// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoweredEquipment.h"
#include "Torch.generated.h"

class USpotLightComponent;

UCLASS()
class EVIDENCE_API ATorch : public APoweredEquipment
{
	GENERATED_BODY()

public:
	ATorch();

protected:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* LightComponent;
};
