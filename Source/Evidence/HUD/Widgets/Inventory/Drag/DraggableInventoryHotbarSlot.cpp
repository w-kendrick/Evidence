// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableInventoryHotbarSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlotDragPreview.h"
#include "InventorySlotDragDropOperation.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragDropOperation.h"
#include "Evidence/HUD/Widgets/Locker/LockerSlotWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

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
	DragOperation->SpawnInitialize(InventoryIndex, InventoryComponent, this);

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

	PerformSwap(InventoryIndex, Index);

	return true;
}

void UDraggableInventoryHotbarSlot::PerformSwap(const uint8 InventorySlot, const uint8 LockerSlot)
{
	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = InventorySlot;
	Data->HitResult.ElementIndex = LockerSlot;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPlayerPawn(), FGameplayTag::RequestGameplayTag(FName(TEXT("GameplayEvent.LockerSwap"))), Payload);
}
