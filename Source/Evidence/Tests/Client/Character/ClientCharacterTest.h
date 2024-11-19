// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "MPTestHelpersBPLibrary.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/TriggerBox.h"
#include "ClientCharacterTest.generated.h"

struct FPlayerTestInfo
{
	APlayerController* PlayerController;
	ABaseCharacter* MyCharacter;
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	ABaseCharacter* OtherCharacter;
};

class UInputAction;

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientCharacterTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	AClientCharacterTest();
	void StartTest() override;
	bool IsReady_Implementation() override;

protected:
	bool bTestHasBegun;

	void BindTriggers();

	UFUNCTION()
	virtual void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	virtual void OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	FPlayerTestInfo Client1TestInfo;
	FPlayerTestInfo Client2TestInfo;

	void CheckResult();

	bool bClient1Passed;
	bool bClient2Passed;

	void InjectInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value);
	void StartInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value);
	void StopInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action);

private:
	void GetOtherClient(const uint8 PlayerIndex, FPlayerTestInfo& PlayerTestInfo) const;
	bool IsPlayerReady(const uint8 PlayerIndex, FPlayerTestInfo& PlayerTestInfo) const;

	UPROPERTY()
	ATriggerBox* TriggerBox1;

	UPROPERTY()
	ATriggerBox* TriggerBox2;
};
