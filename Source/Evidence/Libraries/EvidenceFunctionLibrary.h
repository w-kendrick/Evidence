// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EvidenceFunctionLibrary.generated.h"

class AHub;
class AMapInfoActor;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static AHub* GetHub(UWorld* World);
	static AMapInfoActor* GetMapInfo(UWorld* World);
	
};
