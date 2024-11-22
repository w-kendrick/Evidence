// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ServerHotbarQuickSelectTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerHotbarQuickSelectTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AServerHotbarQuickSelectTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar1Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar2Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar3Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar4Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar5Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar6Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar7Action;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Hotbar8Action;

	int32 ExpectedIndex;
	bool bFirstCycle;

	void Cycle();

	UInputAction* ChooseInputAction() const;
	
};
