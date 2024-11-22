// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "InitialHealthTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AInitialHealthTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AInitialHealthTest();

	void Tick(float DeltaTime) override;

private:
	static constexpr float EXPECTED_HEALTH = 100.f;
	static constexpr float EXPECTED_MAX_HEALTH = 100.f;
	
};
