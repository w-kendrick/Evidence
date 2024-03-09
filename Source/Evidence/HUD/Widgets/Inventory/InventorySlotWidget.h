// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentWidget.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UInventorySlotWidget : public UEquipmentWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(class UInventoryComponent* Comp, const EEquipmentID Object, const uint8 InventoryIndex);

protected:
	virtual void NativeConstruct() override;

	uint8 Index;

	virtual void ButtonLeftClicked() override;
	virtual void ButtonRightClicked() override;
};
