// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "PowerEquipment.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API APowerEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	APowerEquipment();

	virtual void Tick(float DeltaTime) override;

	FOnPowerChanged OnPowerChanged;
	FOnActiveChanged OnActiveChanged;

	UPROPERTY(EditDefaultsOnly)
	float ActiveDrainRate;

	void SetPower(const float NewPower);
	void SetPowerActive(const bool NewActive, const bool bMulticast = false);

	void ToggleActivation();

	float GetPower() const { return Power; }
	float GetMaxPower() const { return MaxPower; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	float MaxPower;

	UPROPERTY(ReplicatedUsing = OnRep_Power, SaveGame)
	float Power;

	bool isPowerActive;

	UFUNCTION()
	void OnRep_Power(const float PrevPower);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetPowerActive(const bool NewActive);

	virtual void ActivatePower();
	virtual void DeactivatePower();
	
};
