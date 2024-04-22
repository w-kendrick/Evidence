// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hub.generated.h"

class AEquipment;
class AMovementSensor;
class ARadialSensor;

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	FTransform Transform;

	UPROPERTY()
	TSubclassOf<AEquipment> Class;
};
	
UCLASS()
class EVIDENCE_API AHub : public AActor
{
	GENERATED_BODY()
	
public:	
	AHub();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FSpawnInfo> InitialSpawns;

	void OnMovementSensed(AMovementSensor* Sensor);
	void OnRadiusSensed(ARadialSensor* Sensor, const TArray<FVector> Locations);

private:
	void CreateInitialSpawns();
	void SpawnEquipment(const FSpawnInfo SpawnInfo);
	void SpawnMovementSensor();
	void SpawnRadialSensor();
};
