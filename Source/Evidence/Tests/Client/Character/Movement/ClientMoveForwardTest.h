// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Client/Character/ClientCharacterTest.h"
#include "ClientMoveForwardTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientMoveForwardTest : public AClientCharacterTest
{
	GENERATED_BODY()

public:
	AClientMoveForwardTest();

	void StartTest() override;

protected:
	void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
};
