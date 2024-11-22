// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerInventoryCycleDownTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerInventoryCycleDownTest : public ACharacterTest
{
	GENERATED_BODY()
	
public:
	AServerInventoryCycleDownTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* CycleDownAction;

	int32 ExpectedIndex;
	bool bFirstCycle;

	void Cycle();

};
