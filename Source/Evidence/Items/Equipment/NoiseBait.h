// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "NoiseBait.generated.h"

UCLASS()
class EVIDENCE_API ANoiseBait : public AEquipment, public IPowerInterface
{
	GENERATED_BODY()

public:
	ANoiseBait();

	virtual UPowerComponent* GetPowerComponent() const override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UPowerComponent* PowerComponent;

	virtual void Activate() override;
	virtual void Deactivate() override;

	UPROPERTY(EditDefaultsOnly)
	float EventDelay;

private:
	FTimerHandle SoundHandle;
	
	void SoundEvent();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSoundEffect();
};
