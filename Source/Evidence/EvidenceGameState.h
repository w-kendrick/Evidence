// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Enums/EquipmentID.h"
#include "EvidenceGameState.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	TSubclassOf<AEquipment> GetEquipmentClass(const EEquipmentID ID) const;
	EEquipmentID GetEquipmentID(const TSubclassOf<AEquipment> Class) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<EEquipmentID, TSubclassOf<AEquipment>> ID_To_Class;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<AEquipment>, EEquipmentID> Class_To_ID;
	
};
