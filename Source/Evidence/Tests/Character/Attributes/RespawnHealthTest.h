// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "RespawnHealthTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ARespawnHealthTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	ARespawnHealthTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> KillPlayerEffectClass;

private:
	float Expected_Health;

	bool bPassedFirstCheck;
	
};
