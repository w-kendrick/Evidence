// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientJumpTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientJumpTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientJumpTest();

	void StartTest() override;

protected:
	void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;
	
};
