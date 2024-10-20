// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),
	Jump		UMETA(DisplayName = "Jump"),
	Sprint		UMETA(DisplayName = "Sprint"),
	Crouch		UMETA(DisplayName = "Crouch"),
	Interact	UMETA(DisplayName = "Interact"),
	Drop		UMETA(DisplayName = "Drop"),
	Use			UMETA(DisplayName = "Use"),
	Reload		UMETA(DisplayName = "Reload"),
	Underbarrel	UMETA(DisplayName = "Underbarrel"),
	MAX			UMETA(DisplayName = "MAX")
};