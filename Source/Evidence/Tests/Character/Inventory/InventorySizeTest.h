// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "InventorySizeTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AInventorySizeTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AInventorySizeTest();

	void StartTest() override;
	
};
