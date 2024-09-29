// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerSessions/GameInstances/MultiplayerGameInstance.h"
#include "EvidenceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceGameInstance : public UMultiplayerGameInstance
{
	GENERATED_BODY()

public:
	UEvidenceGameInstance(const FObjectInitializer& ObjectInitializer);

	FString GetSlotName() const { return SlotName; }

private:
	FString SlotName;
	
};
