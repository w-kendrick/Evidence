// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProneCharacter.h"
#include "BaseCharacter.generated.h"

class UInventoryManagerComponent;
class AEquipment;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ABaseCharacter : public AProneCharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Pickup(AEquipment* const Equipment);
	virtual void Drop();

	AEquipment* GetEquipped() const;

	virtual const FVector GetTraceStart() const;
	virtual const FVector GetTraceDirection() const;

	UInventoryManagerComponent* GetInventoryComponent() const { return InventoryManagerComponent; }

protected:
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent* InventoryManagerComponent;
	
};
