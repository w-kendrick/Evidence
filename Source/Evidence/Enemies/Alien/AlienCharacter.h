// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "AlienCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class EVIDENCE_API AAlienCharacter : public AEvidenceCharacter
{
	GENERATED_BODY()

public:
	AAlienCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UBehaviorTree* GetBehaviourTree() const { return Tree; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* Tree;
	
};
