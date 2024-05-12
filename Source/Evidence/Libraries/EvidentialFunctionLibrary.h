// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EvidentialFunctionLibrary.generated.h"

struct FEvidentialInfo;

UCLASS()
class EVIDENCE_API UEvidentialFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static float CalculateCash(const TArray<FEvidentialInfo>& InfoArray);

	static constexpr float MaxAudioRange = 1000.f;
};
