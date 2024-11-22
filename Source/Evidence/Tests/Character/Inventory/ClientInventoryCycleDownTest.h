// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientInventoryCycleDownTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInventoryCycleDownTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientInventoryCycleDownTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* CycleDownAction;

	int32 ExpectedIndex;
	bool bFirstCycle;

	void Cycle();
	
};
