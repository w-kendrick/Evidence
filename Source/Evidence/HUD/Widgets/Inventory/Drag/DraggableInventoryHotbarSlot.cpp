// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableInventoryHotbarSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlotDragPreview.h"
#include "InventorySlotDragDropOperation.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

void UDraggableInventoryHotbarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayer())
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(GetOwningPlayer()->GetCharacter());
		if (Character)
		{
			InventoryComponent = Character->GetInventoryComponent();
		}
	}
}

void UDraggableInventoryHotbarSlot::SetIndex(const uint8 Index)
{
	InventoryIndex = Index;
}

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
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UInventorySlotDragPreview* DragPreview = CreateWidget<UInventorySlotDragPreview>(this, DragPreviewClass);
	DragPreview->SetIndex(InventoryIndex);
	DragPreview->SetInventoryComponent(InventoryComponent);
	DragPreview->SetColour(FColor::Black);

	UInventorySlotDragDropOperation* DragWidget = Cast<UInventorySlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragWidgetClass));
	DragWidget->DefaultDragVisual = DragPreview;
	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->SpawnInitialize(InventoryIndex, InventoryComponent);

	OutOperation = DragWidget;
}
