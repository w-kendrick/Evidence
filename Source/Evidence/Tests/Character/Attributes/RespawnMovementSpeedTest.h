// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "RespawnMovementSpeedTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ARespawnMovementSpeedTest : public AMasterTest
{
	GENERATED_BODY()

public:
	ARespawnMovementSpeedTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> KillPlayerEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ZeroMovementSpeedEffectClass;

private:
	static constexpr float DEATH_HEALTH = 0.f;
	static constexpr float RESPAWN_MOVEMENT_SPEED = 600.f;

	bool bPassedFirstCheck;
	
};
