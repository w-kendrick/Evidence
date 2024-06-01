// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Enums/EvidentialMedium.h"
#include "Evidence/Structs/EvidentialInfo.h"
#include "Evidence/Libraries/EvidentialFunctionLibrary.h"
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

	float GetWorth() const
	{
		float Worth = 0.0f;

		for (const FEvidentialInfo& Info : Infos)
		{
			Worth += UEvidentialFunctionLibrary::GetWorth(Info.Type, Medium);
		}

		Worth += GetVarietyBonus();

		return Worth;
	}

	float GetVarietyBonus() const
	{
		constexpr float BonusPerType = 10.f;
		TArray<EEvidentialType> Types;

		for (const FEvidentialInfo& Info : Infos)
		{
			if (!Types.Contains(Info.Type))
			{
				Types.Add(Info.Type);
			}
		}

		return Types.Num() * BonusPerType;
	}
};