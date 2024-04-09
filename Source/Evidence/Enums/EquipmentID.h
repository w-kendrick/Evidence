// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEquipmentID : uint8
{
	Empty    UMETA(DisplayName = "Empty"),
	Test1    UMETA(DisplayName = "Test1"),
	Test2    UMETA(DisplayName = "Test2"),
	Rifle    UMETA(DisplayName = "Rifle"),
	Torch    UMETA(DisplayName = "Torch"),
	MAX      UMETA(DisplayName = "MAX")
};