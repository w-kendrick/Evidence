// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "Torch.generated.h"

class USpotLightComponent;

UCLASS()
class EVIDENCE_API ATorch : public APowerEquipment
{
	GENERATED_BODY()

public:
	ATorch();

protected:
	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* LightComponent;
};
