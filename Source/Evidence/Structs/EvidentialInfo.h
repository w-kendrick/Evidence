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
	uint8 Index;

	FEvidentialInfo(const EEvidentialType NewType, const uint8 NewIndex)
		: Type(NewType), Index(NewIndex)
	{

	}

	FEvidentialInfo(const FEvidentialInfo& Other)
		: Type(Other.Type), Index(Other.Index)
	{
		
	}

	FEvidentialInfo()
		: Type(EEvidentialType::Alien), Index(0U)
	{
		
	}
};