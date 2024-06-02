// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "PlantableEquipment.generated.h"

UCLASS()
class EVIDENCE_API APlantableEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	APlantableEquipment();

	virtual void Plant();
	bool CanPlant() const;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void GetPlantPoint(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(ReplicatedUsing=OnRep_IsPlanted)
	bool isPlanted;

	UFUNCTION()
	void OnRep_IsPlanted(const bool PrevIsPlaced);
};
