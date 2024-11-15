// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableInventoryHotbarSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlotDragPreview.h"
#include "InventorySlotDragDropOperation.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

FReply UDraggableInventoryHotbarSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton) && InventoryComponent) //&& InventoryComponent->GetEquipmentAtIndex(InventoryIndex))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UDraggableInventoryHotbarSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UInventorySlotDragPreview* DragPreview = CreateWidget<UInventorySlotDragPreview>(this, DragPreviewClass);
	DragPreview->SetIndex(InventoryIndex);
	DragPreview->SetInventoryComponent(InventoryComponent);
	DragPreview->SetColour(FColor::White);

	UInventorySlotDragDropOperation* DragOperation = Cast<UInventorySlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragOperationClass));
	DragOperation->DefaultDragVisual = DragPreview;
	DragOperation->Pivot = EDragPivot::MouseDown;
	DragOperation->SpawnInitialize(InventoryIndex, InventoryComponent);

	OutOperation = DragOperation;

	SetVisibility(ESlateVisibility::Hidden);
}

void UDraggableInventoryHotbarSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	SetVisibility(ESlateVisibility::Visible);
}
