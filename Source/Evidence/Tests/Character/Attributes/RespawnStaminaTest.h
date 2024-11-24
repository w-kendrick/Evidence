// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "RespawnStaminaTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ARespawnStaminaTest : public AMasterTest
{
	GENERATED_BODY()

public:
	ARespawnStaminaTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> KillPlayerEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ZeroStaminaEffectClass;

private:
	static constexpr float DEATH_HEALTH = 0.f;
	static constexpr float RESPAWN_STAMINA = 100.f;

	bool bPassedFirstCheck;
	
};
