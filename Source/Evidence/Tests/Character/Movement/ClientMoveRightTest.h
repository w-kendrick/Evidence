// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/ClientCharacterTest.h"
#include "ClientMoveRightTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientMoveRightTest : public AClientCharacterTest
{
	GENERATED_BODY()

public:
	AClientMoveRightTest();

	void StartTest() override;

protected:
	void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
};
