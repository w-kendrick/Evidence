// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Tripod.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ATripod : public AEquipment
{
	GENERATED_BODY()

public:
	ATripod();

	void Plant();
	virtual void Pickup(AEvidenceCharacter* Char) override;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	AEquipment* EmplacedEquipment;

	UPROPERTY(Replicated)
	bool isPlaced;
};
