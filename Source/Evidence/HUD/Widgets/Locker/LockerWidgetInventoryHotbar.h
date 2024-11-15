// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/Inventory/InventoryHotbar.h"
#include "LockerWidgetInventoryHotbar.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ULockerWidgetInventoryHotbar : public UInventoryHotbar
{
	GENERATED_BODY()

private:
	void OnEquippedIndexChanged(uint8 SelectedIndex, uint8 PrevIndex) override;
	
};
