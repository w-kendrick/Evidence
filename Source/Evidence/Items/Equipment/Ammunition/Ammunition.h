// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Ammunition.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuantityChanged, uint8);

UCLASS()
class EVIDENCE_API AAmmunition : public AEquipment
{
	GENERATED_BODY()

public:
	AAmmunition();

	FOnQuantityChanged OnQuantityChanged;

	uint8 GetQuantity() const { return Quantity; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxQuantity;

	UPROPERTY(ReplicatedUsing=OnRep_Quantity)
	uint8 Quantity;

	UFUNCTION()
	void OnRep_Quantity(const uint8 OldQuantity);
	
};
