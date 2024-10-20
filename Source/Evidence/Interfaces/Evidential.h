// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Evidence/Enums/EvidentialType.h"
#include "Evidential.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEvidential : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EVIDENCE_API IEvidential
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetBaseWorth() const = 0;
	virtual EEvidentialType GetType() const = 0;
};
