// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentWidget.h"
#include "InventorySlotWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UInventorySlotWidget : public UEquipmentWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(class UInventoryComponent* Comp, AEquipment* NewEquipment, const uint8 InventoryIndex);

protected:
	uint8 Index;

	virtual void ButtonLeftClicked() override;
	virtual void ButtonRightClicked() override;
};
