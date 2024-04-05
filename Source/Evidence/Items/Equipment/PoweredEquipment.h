// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "PoweredEquipment.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPowerChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveChanged, bool);

UCLASS()
class EVIDENCE_API APoweredEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	APoweredEquipment();

	FOnPowerChanged OnPowerChanged;
	FOnActiveChanged OnActiveChanged;

	void SetPower(const float NewPower);
	void SetActive(const bool NewActive);

	void ToggleActivation();
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float ActiveDrainRate;

	UPROPERTY(EditDefaultsOnly)
	float MaxPower;

	UPROPERTY(ReplicatedUsing = OnRep_Power)
	float Power;

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool isActive;

	UFUNCTION()
	void OnRep_Power(const float PrevPower);

	UFUNCTION()
	void OnRep_IsActive(const bool PrevIsActive);

	virtual void Activate() {};
	virtual void Deactivate() {};
};
