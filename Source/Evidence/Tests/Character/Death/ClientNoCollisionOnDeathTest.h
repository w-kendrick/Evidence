// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ClientNoCollisionOnDeathTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientNoCollisionOnDeathTest : public AMasterTest
{
	GENERATED_BODY()
	
public:
	AClientNoCollisionOnDeathTest();

	void StartTest() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> KillPlayerEffectClass;

private:
	void OnDeath();
	void OnRespawn();
};
