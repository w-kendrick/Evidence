// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Save/ActorSaveData.h"
#include "Evidence/Items/Equipment.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "PlayerSave.generated.h"

USTRUCT()
struct FPlayerSave
{
	GENERATED_BODY()

	TArray<FEquipmentSaveData> SavedEquipment;

	FPlayerSave()
	{

	}

	void AddEquipment(FEquipmentSaveData EquipmentData)
	{
		SavedEquipment.Add(EquipmentData);
	}
};