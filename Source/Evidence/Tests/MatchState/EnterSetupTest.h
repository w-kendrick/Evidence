// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "EnterSetupTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AEnterSetupTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AEnterSetupTest();

	void StartTest() override;

private:
	bool bGameModePassed = false;

	void OnServerMatchStateChanged(FName State);
	void OnClient1MatchStateChanged(FName State);
	void OnClient2MatchStateChanged(FName State);
};
