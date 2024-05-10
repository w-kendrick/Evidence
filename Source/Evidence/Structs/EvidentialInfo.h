// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Enums/EvidentialType.h"
#include "Evidence/Enums/EvidentialMedium.h"
#include "EvidentialInfo.generated.h"

USTRUCT()
struct FEvidentialInfo
{
	GENERATED_BODY();

	EEvidentialType Type;
	EEvidentialMedium Medium;
	float BaseCash;

	FEvidentialInfo(const EEvidentialType NewType, const EEvidentialMedium NewMedium, const float NewCash)
		: Type(NewType), Medium(NewMedium), BaseCash(NewCash)
	{

	}

	FEvidentialInfo() 
	{
		Type = EEvidentialType::Alien;
		Medium = EEvidentialMedium::Photo;
		BaseCash = 1.0f;
	}
};