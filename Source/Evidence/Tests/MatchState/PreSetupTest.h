// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "PreSetupTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API APreSetupTest : public AMasterTest
{
	GENERATED_BODY()

public:
	APreSetupTest();

	void StartTest() override;
};
