// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerMoveLeftTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerMoveLeftTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AServerMoveLeftTest();

	void StartTest() override;

protected:
	void OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
};
