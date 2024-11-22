// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerStaminaCapTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerStaminaCapTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AServerStaminaCapTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AwardStaminaEffectClass;

	static constexpr float MAX_STAMINA = 100.f;
	
};
