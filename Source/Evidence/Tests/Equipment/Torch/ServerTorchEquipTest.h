// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerTorchEquipTest.generated.h"

class ATorch;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerTorchEquipTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerTorchEquipTest();

	void StartTest() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* DropAction;

private:
	UPROPERTY()
	ATorch* ServerTorch = nullptr;

	UPROPERTY()
	ATorch* Client1Torch = nullptr;

	UPROPERTY()
	ATorch* Client2Torch = nullptr;

	void OnEquip();
	void OnDrop();
	
};
