// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerTorchPowerDrainTest.generated.h"

class ATorch;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerTorchPowerDrainTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerTorchPowerDrainTest();

	void StartTest() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* UseAction;

private:
	UPROPERTY()
	ATorch* ServerTorch = nullptr;

	UPROPERTY()
	ATorch* Client1Torch = nullptr;

	UPROPERTY()
	ATorch* Client2Torch = nullptr;

	float PowerAtDeactivation = 0.0f;

	void OnEquip();
	void OnActivate();
	void OnDeactivate();
	
};
