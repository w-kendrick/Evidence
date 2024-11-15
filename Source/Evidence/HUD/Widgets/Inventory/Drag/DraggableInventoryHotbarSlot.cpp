// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableInventoryHotbarSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlotDragPreview.h"
#include "InventorySlotDragDropOperation.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragDropOperation.h"
#include "Evidence/HUD/Widgets/Locker/LockerSlotWidget.h"

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

bool UDraggableInventoryHotbarSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	ULockerSlotDragDropOperation* const LockerSlotDragDropOperation = Cast<ULockerSlotDragDropOperation>(InOperation);

	if (!LockerSlotDragDropOperation)
	{
		return false;
	}

	const uint8 Index = LockerSlotDragDropOperation->GetIndex();
	ULockerSlotWidget* const WidgetSource = LockerSlotDragDropOperation->GetWidgetSource();
	WidgetSource->SetVisibility(ESlateVisibility::Visible);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Swap Locker: ") + FString::FromInt(Index) + FString(" / Inventory: ") + FString::FromInt(InventoryIndex));

	return true;
}
