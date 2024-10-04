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

	void AddEquipment(AEquipment* const Equipment, const uint8 EquipmentID)
	{
		FEquipmentSaveData ActorData;
		ActorData.EquipmentID = EquipmentID;

		// Pass the array to fill with data from Actor
		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Equipment->Serialize(Ar);

		SavedEquipment.Add(ActorData);
	}
};