// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableInventoryHotbarSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlotDragPreview.h"
#include "InventorySlotDragDropOperation.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

FReply UDraggableInventoryHotbarSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton) && InventoryComponent && InventoryComponent->GetEquipmentAtIndex(InventoryIndex))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UDraggableInventoryHotbarSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	
}
