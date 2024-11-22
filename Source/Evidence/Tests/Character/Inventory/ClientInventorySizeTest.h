// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientInventorySizeTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInventorySizeTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientInventorySizeTest();

	void StartTest() override;
	
};
