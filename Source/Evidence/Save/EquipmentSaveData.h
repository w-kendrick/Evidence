// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Structs/EquipmentList.h"
#include "EquipmentSaveData.generated.h"

USTRUCT()
struct FEquipmentSaveData
{
	GENERATED_BODY()

public:
	/* Identifier for which Equipment this belongs to */
	UPROPERTY()
	uint8 EquipmentID;

	/* Contains all 'SaveGame' marked variables of the Equipment */
	UPROPERTY()
	TArray<uint8> ByteData;
};