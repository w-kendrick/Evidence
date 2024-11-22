// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientInitialStaminaTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInitialStaminaTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientInitialStaminaTest();

	void StartTest() override;
	
};
