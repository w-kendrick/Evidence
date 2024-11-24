// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "InitialMovementSpeedTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AInitialMovementSpeedTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AInitialMovementSpeedTest();

	void Tick(float DeltaTime) override;

private:
	static constexpr float EXPECTED_MOVEMENT_SPEED = 600.f;
	static constexpr float EXPECTED_MAX_MOVEMENT_SPEED = 1200.f;
	
};
