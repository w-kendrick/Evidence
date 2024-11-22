// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerHealthCapTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerHealthCapTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AServerHealthCapTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AwardHealthEffectClass;

	static constexpr float MAX_HEALTH = 100.f;
	
};
