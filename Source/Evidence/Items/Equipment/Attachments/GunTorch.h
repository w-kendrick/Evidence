// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "GunTorch.generated.h"

class USpotLightComponent;

UCLASS()
class EVIDENCE_API AGunTorch : public AEquipmentAttachment, public IPowerInterface
{
	GENERATED_BODY()

public:
	AGunTorch();

	virtual UPowerComponent* GetPowerComponent() const override;

protected:
	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* LightComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
	UPowerComponent* PowerComponent;
};
