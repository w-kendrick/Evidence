// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Client/Character/ClientCharacterTest.h"
#include "ClientCrouchTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientCrouchTest : public AClientCharacterTest
{
	GENERATED_BODY()

public:
	AClientCrouchTest();

	void StartTest() override;

protected:
	void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
};
