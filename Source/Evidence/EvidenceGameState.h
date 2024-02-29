// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Enums/EquipmentID.h"
#include "EvidenceGameState.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameState
{
	GENERATED_BODY()

public:
	AEvidenceGameState();
	TSubclassOf<AEquipment> GetEquipmentClass(const EEquipmentID ID);

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<EEquipmentID, TSubclassOf<AEquipment>> ID_To_Class;

	TMap<TSubclassOf<AEquipment>, EEquipmentID> Class_To_ID;
	
};
