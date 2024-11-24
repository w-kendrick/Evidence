// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/Character/CharacterTest.h"
#include "ClientLookLeftTest.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API AClientLookLeftTest : public ACharacterTest
{
	GENERATED_BODY()

public:
	AClientLookLeftTest();

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
