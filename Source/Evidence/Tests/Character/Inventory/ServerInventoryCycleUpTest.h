// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerInventoryCycleUpTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerInventoryCycleUpTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AServerInventoryCycleUpTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* CycleUpAction;

	uint8 ExpectedIndex;
	bool bFirstCycle;

	void Cycle();
	
};
