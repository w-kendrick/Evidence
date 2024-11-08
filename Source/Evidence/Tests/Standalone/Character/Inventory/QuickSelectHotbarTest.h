// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Standalone/Character/CharacterTest.h"
#include "QuickSelectHotbarTest.generated.h"

class UInputAction;

/**
 * Test for quick selecting hotbar slots
 */
UCLASS()
class EVIDENCE_API AQuickSelectHotbarTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	void StartTest() override;
	void Tick(float DeltaTime) override;
	void TestNextSlot();

	uint8 CurrentSlotToTest = 8;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot1;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot2;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot3;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot4;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot5;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot6;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot7;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HotbarSlot8;
	
};
