// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Delegates.h"
#include "PowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPowerComponent();

	FOnPowerChanged OnPowerChanged;
	FOnActiveChanged OnActiveChanged;

	UPROPERTY(EditDefaultsOnly)
	float ActiveDrainRate;

	void SetPower(const float NewPower);
	void SetPowerActive(const bool NewActive);

	void ToggleActivation();

	float GetPower() const { return Power; }
	float GetMaxPower() const { return MaxPower; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	float MaxPower;

	UPROPERTY(ReplicatedUsing = OnRep_Power)
	float Power;

	UPROPERTY(ReplicatedUsing = OnRep_IsPowerActive)
	bool isPowerActive;

	UFUNCTION()
	void OnRep_Power(const float PrevPower);

	UFUNCTION()
	void OnRep_IsPowerActive(const bool PrevIsActive);

	void ActivatePower();
	void DeactivatePower();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
