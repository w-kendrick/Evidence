// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvidenceCaptureEquipment.h"
#include "Swab.generated.h"

class ABloodStain;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ASwab : public AEvidenceCaptureEquipment
{
	GENERATED_BODY()

public:
	ASwab();

	void ApplyToBloodStain(ABloodStain* const Stain);
	
};
