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
	uint8 Index;

	FEvidentialInfo(const EEvidentialType NewType, const float NewCash, const uint8 NewIndex)
		: Type(NewType), BaseCash(NewCash), Index(NewIndex)
	{

	}

	FEvidentialInfo(const FEvidentialInfo& Other)
		: Type(Other.Type), BaseCash(Other.BaseCash), Index(Other.Index)
	{
		
	}

	FEvidentialInfo()
		: Type(EEvidentialType::Alien), BaseCash(1.0f), Index(0U)
	{
		
	}
};