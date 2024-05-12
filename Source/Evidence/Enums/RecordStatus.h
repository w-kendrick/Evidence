// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ERecordStatus : uint8
{
	PreRecording	UMETA(DisplayName = "Pre-recording"),
	Recording		UMETA(DisplayName = "Recording"),
	PostRecording	UMETA(DisplayName = "Post-recording"),
	MAX				UMETA(DisplayName = "MAX")
};