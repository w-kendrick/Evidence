// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerTorchActivationTest.generated.h"

class ATorch;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerTorchActivationTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerTorchActivationTest();

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

	void OnEquip();
	void OnActivate();
	void OnDeactivate();
	
};
