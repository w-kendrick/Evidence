// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/Inventory/InventoryHotbarSlot.h"
#include "DraggableInventoryHotbarSlot.generated.h"

class UInventorySlotDragPreview;
class UInventorySlotDragDropOperation;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UDraggableInventoryHotbarSlot : public UInventoryHotbarSlot
{
	GENERATED_BODY()

protected:
	FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotDragPreview> DragPreviewClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotDragDropOperation> DragOperationClass;

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouseButton;

private:
	void PerformSwap(const uint8 InventorySlot, const uint8 LockerSlot);
};
