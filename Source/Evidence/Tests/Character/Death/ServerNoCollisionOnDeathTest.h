// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerNoCollisionOnDeathTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerNoCollisionOnDeathTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerNoCollisionOnDeathTest();

	void StartTest() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> KillPlayerEffectClass;

private:
	void OnDeath();
	void OnRespawn();
	
};
