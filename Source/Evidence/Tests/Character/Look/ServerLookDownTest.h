// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "ServerLookDownTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AServerLookDownTest : public AMasterTest
{
	GENERATED_BODY()

public:
	AServerLookDownTest();

	void StartTest() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> Objects;

private:
	bool Check(ABaseCharacter* Character);
	
};
