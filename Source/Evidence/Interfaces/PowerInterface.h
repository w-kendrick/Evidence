// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Evidence/Items/Equipment/Components/PowerComponent.h"
#include "PowerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPowerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EVIDENCE_API IPowerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPowerComponent* GetPowerComponent() const = 0;

	virtual void Activate();
	virtual void Deactivate();
};
