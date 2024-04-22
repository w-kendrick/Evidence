// Fill out your copyright notice in the Description page of Project Settings.


#include "Hub.h"
#include "Equipment/Sensors/MovementSensor.h"
#include "Equipment/RadialSensor.h"

AHub::AHub()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHub::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CreateInitialSpawns();
	}
}

void AHub::CreateInitialSpawns()
{
	for (const FSpawnInfo SpawnInfo : InitialSpawns)
	{
		SpawnEquipment(SpawnInfo);
	}
}

void AHub::SpawnEquipment(const FSpawnInfo SpawnInfo)
{
	const FTransform& Transform = SpawnInfo.Transform;
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	if (Class == AMovementSensor::StaticClass())
	{
		AMovementSensor* MovementSensor = Cast<AMovementSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
		MovementSensor->OnMovementSense.AddUObject(this, &ThisClass::OnMovementSensed);
	}
	if (Class == ARadialSensor::StaticClass())
	{
		ARadialSensor* RadialSensor = Cast<ARadialSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
		RadialSensor->OnRadialSense.AddUObject(this, &ThisClass::OnRadiusSensed);
	}
}

void AHub::SpawnMovementSensor()
{

}

void AHub::SpawnRadialSensor()
{

}

void AHub::OnMovementSensed(AMovementSensor* Sensor)
{

}

void AHub::OnRadiusSensed(ARadialSensor* Sensor, const TArray<FVector> Locations)
{

}
