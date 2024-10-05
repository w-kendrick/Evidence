// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"
#include "GunTorch.generated.h"

class USpotLightComponent;

UCLASS()
class EVIDENCE_API AGunTorch : public AEquipmentAttachment
{
	GENERATED_BODY()

public:
	AGunTorch();

protected:
	void Activate();
	void Deactivate();

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* LightComponent;
};
