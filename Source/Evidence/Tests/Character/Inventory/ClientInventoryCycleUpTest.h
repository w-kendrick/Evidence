// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientInventoryCycleUpTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInventoryCycleUpTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientInventoryCycleUpTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* CycleUpAction;

	uint8 ExpectedIndex;
	bool bFirstCycle;

	void Cycle();
};
