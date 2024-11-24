// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ClientStaminaCapTest.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientStaminaCapTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AClientStaminaCapTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AwardStaminaEffectClass;

	static constexpr float MAX_STAMINA = 100.f;
	
};
