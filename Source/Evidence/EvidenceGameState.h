// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EvidenceGameState.generated.h"

class AHub;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AHub* GetHub();

protected:
	UPROPERTY()
	AHub* Hub;
	
};
