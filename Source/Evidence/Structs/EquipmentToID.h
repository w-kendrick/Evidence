// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentToID.generated.h"

class AEquipment;

USTRUCT(BlueprintType)
struct FEquipmentToID
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> Class;

	UPROPERTY(EditDefaultsOnly)
	uint8 ID;
};