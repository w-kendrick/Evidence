// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "TorchDefaultsTest.generated.h"

class ATorch;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ATorchDefaultsTest : public AMasterTest
{
	GENERATED_BODY()

public:
	ATorchDefaultsTest();

	void StartTest() override;

private:
	UPROPERTY()
	ATorch* ServerTorch = nullptr;

	UPROPERTY()
	ATorch* Client1Torch = nullptr;

	UPROPERTY()
	ATorch* Client2Torch = nullptr;
	
};
