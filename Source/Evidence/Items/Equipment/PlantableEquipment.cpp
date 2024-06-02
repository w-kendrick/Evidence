// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantableEquipment.h"
#include "Net/UnrealNetwork.h"

APlantableEquipment::APlantableEquipment()
{
}

void APlantableEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlantableEquipment, isPlanted);
}

void APlantableEquipment::Plant()
{
	isPlanted = true;
}

bool APlantableEquipment::CanPlant() const
{
	return true;
}

void APlantableEquipment::GetPlantPoint(FVector& Location, FRotator& Rotation) const
{
	Location = GetActorLocation();
	Rotation = GetActorRotation();
}

void APlantableEquipment::OnRep_IsPlanted(const bool PrevIsPlaced)
{
}
