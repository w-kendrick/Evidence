// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "EvidenceCaptureEquipment.generated.h"

UCLASS()
class EVIDENCE_API AEvidenceCaptureEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	AEvidenceCaptureEquipment();

	virtual TArray<FEvidentialCapture> GetCaptures() const;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(Replicated)
	TArray<FEvidentialCapture> Captures;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxCaptures;
	
};
