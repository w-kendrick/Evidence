// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientMoveBackwardTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientMoveBackwardTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientMoveBackwardTest();

	void StartTest() override;

protected:
	void OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
};
