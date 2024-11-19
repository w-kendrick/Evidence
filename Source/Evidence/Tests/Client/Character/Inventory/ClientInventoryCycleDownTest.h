// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Client/Character/ClientCharacterTest.h"
#include "ClientInventoryCycleDownTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInventoryCycleDownTest : public AClientCharacterTest
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
