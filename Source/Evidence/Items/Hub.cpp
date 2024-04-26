// Fill out your copyright notice in the Description page of Project Settings.


#include "Hub.h"
#include "Equipment/Sensors/MovementSensor.h"
#include "Equipment/RadialSensor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Equipment/Projectiles/TrueTrackerDart.h"

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

void AHub::SpawnEquipment(const FSpawnInfo& SpawnInfo)
{
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	if (UKismetMathLibrary::ClassIsChildOf(Class, AMovementSensor::StaticClass()))
	{
		SpawnMovementSensor(SpawnInfo);
	}
	if (UKismetMathLibrary::ClassIsChildOf(Class, ARadialSensor::StaticClass()))
	{
		SpawnRadialSensor(SpawnInfo);
	}
}

void AHub::SpawnMovementSensor(const FSpawnInfo& SpawnInfo)
{
	const FTransform& Transform = SpawnInfo.Transform;
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	AMovementSensor* MovementSensor = Cast<AMovementSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
	MovementSensor->OnMovementSense.AddUObject(this, &ThisClass::OnMovementSensed);
}

void AHub::SpawnRadialSensor(const FSpawnInfo& SpawnInfo)
{
	const FTransform& Transform = SpawnInfo.Transform;
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	ARadialSensor* RadialSensor = Cast<ARadialSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
	RadialSensor->OnRadialSense.AddUObject(this, &ThisClass::OnRadiusSensed);
}

void AHub::SubscribeToTrackerDart(ATrueTrackerDart* Dart)
{
	Dart->OnTrackDartBroadcast.AddUObject(this, &ThisClass::OnDartLocationReceived);
}

void AHub::OnMovementSensed(AMovementSensor* Sensor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Movement sensed");
}

void AHub::OnRadiusSensed(ARadialSensor* Sensor, const TArray<FVector> Locations)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Radius sensed");
}

void AHub::OnDartLocationReceived(ATrueTrackerDart*, const FVector& Location)
{

}
