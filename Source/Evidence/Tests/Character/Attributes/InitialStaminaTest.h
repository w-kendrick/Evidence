// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "InitialStaminaTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AInitialStaminaTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AInitialStaminaTest();

	void Tick(float DeltaTime) override;

private:
	static constexpr float EXPECTED_STAMINA = 100.f;
	static constexpr float EXPECTED_MAX_STAMINA = 100.f;
	
};
