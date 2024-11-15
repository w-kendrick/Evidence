// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventorySlotDragDropOperation.generated.h"

class UInventoryManagerComponent;
class UDraggableInventoryHotbarSlot;

/**
 * Stores information of inventory slot that is dragged and dropped
 */
UCLASS()
class EVIDENCE_API UInventorySlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const uint8 NewIndex, UInventoryManagerComponent* Comp, UDraggableInventoryHotbarSlot* Source);
	uint8 GetIndex() const { return Index; }
	UInventoryManagerComponent* GetInventoryComponent() const { return InventoryComponent; }
	UDraggableInventoryHotbarSlot* GetWidgetSource() const { return WidgetSource;  }

protected:
	uint8 Index;

	UPROPERTY()
	UInventoryManagerComponent* InventoryComponent;

	UPROPERTY()
	UDraggableInventoryHotbarSlot* WidgetSource;
	
};
