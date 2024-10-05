// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "NoiseBait.generated.h"

UCLASS()
class EVIDENCE_API ANoiseBait : public APowerEquipment
{
	GENERATED_BODY()

public:
	ANoiseBait();

protected:
	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;

	UPROPERTY(EditDefaultsOnly)
	float EventDelay;

private:
	FTimerHandle SoundHandle;
	
	void SoundEvent();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSoundEffect();
};
