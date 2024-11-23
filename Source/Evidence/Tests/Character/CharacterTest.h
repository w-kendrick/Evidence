// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "MPTestHelpersBPLibrary.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Evidence/Tests/TestFunctionLibrary.h"
#include "CharacterTest.generated.h"

struct FPlayerTestInfo
{
	APlayerController* PlayerController;
	ABaseCharacter* MyCharacter;
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
};

struct FClientTestInfo : FPlayerTestInfo
{
	ABaseCharacter* ServerCharacter;
	ABaseCharacter* OtherClientCharacter;
};

struct FServerTestInfo : FPlayerTestInfo
{
	ABaseCharacter* Client1Character;
	ABaseCharacter* Client2Character;
};

class UInputAction;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ACharacterTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	ACharacterTest();
	void StartTest() override;
	bool IsReady_Implementation() override;

protected:
	bool bTestHasBegun;

	void BindTriggers();

	UFUNCTION()
	virtual void OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	virtual void OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	virtual void OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	FServerTestInfo ServerTestInfo;
	FClientTestInfo Client1TestInfo;
	FClientTestInfo Client2TestInfo;

	void CheckResult();

	bool bServerPassed;
	bool bClient1Passed;
	bool bClient2Passed;

	void InjectInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value);
	void StartInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value);
	void StopInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action);

private:
	void ServerGetOtherPlayers();
	bool IsServerReady();
	void ClientGetOtherPlayers(const uint8 PlayerIndex, FClientTestInfo& ClientTestInfo, const int32 OtherClientId) const;
	bool IsClientReady(const uint8 PlayerIndex, FClientTestInfo& ClientTestInfo, int32& ClientId) const;

	UPROPERTY()
	ATriggerBox* ServerTriggerBox;

	UPROPERTY()
	ATriggerBox* Client1TriggerBox;

	UPROPERTY()
	ATriggerBox* Client2TriggerBox;

	int32 ServerPlayerId;
	int32 Client1PlayerId;
	int32 Client2PlayerId;
};
