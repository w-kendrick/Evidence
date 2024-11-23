// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientMovementSpeedCapTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientMovementSpeedCapTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientMovementSpeedCapTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> MovementSpeedEffectClass;

	static constexpr float MAX_MOVEMENT_SPEED = 1200.f;
	
};
