// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Structs/EvidentialSpawn.h"
#include "WorldGenerator.generated.h"

class UBoxComponent;

UCLASS()
class EVIDENCE_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldGenerator();

	void SetupWorld();
	void ResetWorld();

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FEvidentialSpawn> ClassesToSpawn;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UBoxComponent> Box;

	void SpawnClassAtLocation(const TSubclassOf<AActor>& Class, const FVector& Location);
	bool GetGroundPoint(const FVector& OriginalPoint, FVector& NewPoint) const;

private:
	UPROPERTY()
	TArray<AActor*> SpawnedActors;
};
