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
	FTransform Transform;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> Class;
};