// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Enums/EvidentialType.h"
#include "EvidentialInfo.generated.h"

USTRUCT()
struct FEvidentialInfo
{
	GENERATED_BODY();

	EEvidentialType Type;
	float BaseCash;

	FEvidentialInfo(const EEvidentialType NewType, const float NewCash)
		: Type(NewType), BaseCash(NewCash)
	{

	}

	FEvidentialInfo(const FEvidentialInfo& Other)
		: Type(Other.Type), BaseCash(Other.BaseCash)
	{
		
	}

	FEvidentialInfo()
		: Type(EEvidentialType::Alien), BaseCash(1.0f)
	{
		
	}
};