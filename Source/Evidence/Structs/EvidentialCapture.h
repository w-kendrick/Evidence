// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Enums/EvidentialMedium.h"
#include "Evidence/Structs/EvidentialInfo.h"
#include "EvidentialCapture.generated.h"

USTRUCT()
struct FEvidentialCapture
{
	GENERATED_BODY();

	EEvidentialMedium Medium;
	TArray<FEvidentialInfo> Infos;

	FEvidentialCapture(const EEvidentialMedium NewMedium, const TArray<FEvidentialInfo>& NewInfo)
		: Medium(NewMedium), Infos(NewInfo)
	{

	}

	FEvidentialCapture()
		: Medium(EEvidentialMedium::Photo), Infos(TArray<FEvidentialInfo>())
	{
		
	}
};