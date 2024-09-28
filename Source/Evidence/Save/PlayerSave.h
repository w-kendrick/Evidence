// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Structs/EquipmentList.h"
#include "PlayerSave.generated.h"

USTRUCT()
struct FPlayerSave
{
	GENERATED_BODY()

	FUniqueNetIdRepl PlayerID;
	FEquipmentList EquipmentList;

	FPlayerSave()
	{

	}

	FPlayerSave(FEquipmentList List)
		: EquipmentList(List)
	{

	}
};