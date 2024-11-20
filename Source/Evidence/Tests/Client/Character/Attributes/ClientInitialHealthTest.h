// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Client/Character/ClientCharacterTest.h"
#include "ClientInitialHealthTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientInitialHealthTest : public AClientCharacterTest
{
	GENERATED_BODY()

public:
	AClientInitialHealthTest();

	void StartTest() override;
	
};
