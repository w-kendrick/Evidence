// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "EnterPostNightTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AEnterPostNightTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AEnterPostNightTest();

	void StartTest() override;

private:
	void OnServerMatchStateChanged(FName State);
	void OnClient1MatchStateChanged(FName State);
	void OnClient2MatchStateChanged(FName State);
};
