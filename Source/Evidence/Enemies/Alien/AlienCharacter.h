// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Interfaces/Evidential.h"
#include "AlienCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class EVIDENCE_API AAlienCharacter : public AEvidenceCharacter, public IEvidential
{
	GENERATED_BODY()

public:
	AAlienCharacter(const FObjectInitializer& ObjectInitializer);

	virtual float GetBaseWorth() const override;
	virtual EEvidentialType GetType() const override;

	FORCEINLINE UBehaviorTree* GetBehaviourTree() const { return Tree; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* Tree;

private:
	UPROPERTY(EditDefaultsOnly)
	float WorthAlive;

	UPROPERTY(EditDefaultsOnly)
	float WorthDead;
	
};
