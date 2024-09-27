// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EvidentialSpawn.generated.h"

class IEvidential;

USTRUCT(BlueprintType)
struct FEvidentialSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Class;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRate;

	FEvidentialSpawn(const TSubclassOf<AActor>& NewClass, const float& NewRate)
		: Class(NewClass), SpawnRate(NewRate)
	{

	}

	FEvidentialSpawn(const FEvidentialSpawn& Info)
		: Class(Info.Class), SpawnRate(Info.SpawnRate)
	{

	}

	FEvidentialSpawn()
		: Class(nullptr), SpawnRate(0.0f)
	{

	}
};