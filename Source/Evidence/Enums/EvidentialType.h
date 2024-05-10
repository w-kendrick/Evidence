// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEvidentialType : uint8
{
	None     UMETA(DisplayName = "None"),
	Alien    UMETA(DisplayName = "Alien"),
	UFO      UMETA(DisplayName = "UFO"),
	Victim   UMETA(DisplayName = "Victim"),
	Tech     UMETA(DisplayName = "Tech"),
	Prints   UMETA(DisplayName = "Prints"),
	Blood    UMETA(DisplayName = "Blood"),
	MAX      UMETA(DisplayName = "MAX")
};