// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpawnInfo.generated.h"

class AEquipment;

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> Class;

	UPROPERTY(EditDefaultsOnly)
	FTransform Transform;

	FSpawnInfo(const TSubclassOf<AEquipment>& NewClass, const FTransform& NewTransform)
		: Class(NewClass), Transform(NewTransform)
	{

	}

	FSpawnInfo(const FSpawnInfo& Info)
		: Class(Info.Class), Transform(Info.Transform)
	{

	}

	FSpawnInfo()
		: Class(nullptr), Transform(FTransform())
	{

	}
};