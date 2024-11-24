// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerUncrouchTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerUncrouchTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerUncrouchTest();

	void StartTest() override;

protected:
	void OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	void OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

private:
	void Step2();
	
};
