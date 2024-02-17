// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None    UMETA(DisplayName = "None"),
	Jump    UMETA(DisplayName = "Jump"),
	MAX     UMETA(DisplayName = "MAX")
};