// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ClientHotbarQuickSelectTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientHotbarQuickSelectTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AClientHotbarQuickSelectTest();

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
