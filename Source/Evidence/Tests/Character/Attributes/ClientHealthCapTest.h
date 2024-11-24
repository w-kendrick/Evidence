// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ClientHealthCapTest.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientHealthCapTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AClientHealthCapTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AwardHealthEffectClass;

	static constexpr float MAX_HEALTH = 100.f;
	
};
