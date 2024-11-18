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
	ABaseCharacter* Character;
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
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
	bool IsReady_Implementation() override;

protected:
	void BindTriggers();

	virtual void OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
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
	bool IsPlayerReady(const uint8 PlayerIndex, FPlayerTestInfo& PlayerTestInfo) const;

};
