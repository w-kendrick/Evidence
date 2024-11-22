// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "InitialStaminaTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AInitialStaminaTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AInitialStaminaTest();

	void Tick(float DeltaTime) override;
	
};
