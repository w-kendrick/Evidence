// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAttachmentType : uint8
{
	Underbarrel     UMETA(DisplayName = "Underbarrel"),
	Scope			UMETA(DisplayName = "Scope"),
	Magazine		UMETA(DisplayName = "Magazine"),
	MAX				UMETA(DisplayName = "MAX")
};