// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hub.generated.h"

class AEquipment;
class AMovementSensor;
class ARadialSensor;
class ATrueTrackerDart;

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FTransform Transform;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> Class;
};
	
UCLASS()
class EVIDENCE_API AHub : public AActor
{
	GENERATED_BODY()
	
public:	
	AHub();

	void SubscribeToTrackerDart(ATrueTrackerDart* Dart);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FSpawnInfo> InitialSpawns;

	void OnMovementSensed(AMovementSensor* Sensor);
	void OnRadiusSensed(ARadialSensor* Sensor, const TArray<FVector> Locations);
	void OnDartLocationReceived(ATrueTrackerDart*, const FVector& Location);

private:
	void CreateInitialSpawns();
	void SpawnEquipment(const FSpawnInfo& SpawnInfo);
	void SpawnMovementSensor(const FSpawnInfo& SpawnInfo);
	void SpawnRadialSensor(const FSpawnInfo& SpawnInfo);
};
