// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEvidentialMedium : uint8
{
	None     UMETA(DisplayName = "None"),
	Audio    UMETA(DisplayName = "Audio"),
	Photo    UMETA(DisplayName = "Photo"),
	Video    UMETA(DisplayName = "Video"),
	Item	 UMETA(DisplayName = "Item"),
	MAX      UMETA(DisplayName = "MAX")
};