// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Hub/Locker.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragPreview.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragDropOperation.h"
#include "Evidence/HUD/Widgets/Inventory/Drag/InventorySlotDragDropOperation.h"
#include "Evidence/HUD/Widgets/Inventory/Drag/DraggableInventoryHotbarSlot.h"
#include "AbilitySystemBlueprintLibrary.h"

void ULockerSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	UpdateSlot(nullptr);
}

FReply ULockerSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton) && Locker) //&& Locker->GetEquipmentAtIndex(InventoryIndex))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void ULockerSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	ULockerSlotDragPreview* DragPreview = CreateWidget<ULockerSlotDragPreview>(this, DragPreviewClass);
	DragPreview->SetIndex(StorageIndex);
	DragPreview->SetLocker(Locker);
	DragPreview->SetColour(FColor::White);

	ULockerSlotDragDropOperation* DragOperation = Cast<ULockerSlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragOperationClass));
	DragOperation->DefaultDragVisual = DragPreview;
	DragOperation->Pivot = EDragPivot::MouseDown;
	DragOperation->SpawnInitialize(StorageIndex, Locker, this);

	OutOperation = DragOperation;

	SetVisibility(ESlateVisibility::Hidden);
}

void ULockerSlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	SetVisibility(ESlateVisibility::Visible);
}

bool ULockerSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventorySlotDragDropOperation* const InventorySlotDragDropOperation = Cast<UInventorySlotDragDropOperation>(InOperation);

	if (!InventorySlotDragDropOperation)
	{
		return false;
	}

	const uint8 Index = InventorySlotDragDropOperation->GetIndex();
	UDraggableInventoryHotbarSlot* const WidgetSource = InventorySlotDragDropOperation->GetWidgetSource();
	WidgetSource->SetVisibility(ESlateVisibility::Visible);

	PerformSwap(Index, StorageIndex);

	return true;
}

void ULockerSlotWidget::PerformSwap(const uint8 InventorySlot, const uint8 LockerSlot)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Swap Locker: ") + FString::FromInt(LockerSlot) + FString(" / Inventory: ") + FString::FromInt(InventorySlot));

	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = InventorySlot;
	Data->HitResult.ElementIndex = LockerSlot;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPlayerPawn(), FGameplayTag::RequestGameplayTag(FName(TEXT("GameplayEvent.LockerSwap"))), Payload);
}

void ULockerSlotWidget::SetIndex(const uint8 NewIndex)
{
	StorageIndex = NewIndex;
}

void ULockerSlotWidget::UpdateSlot(const AEquipment* const Equipment)
{
	if (Equipment)
	{
		NameText->SetText(FText::FromString(Equipment->GetEquipmentName()));
	}
	else
	{
		NameText->SetText(FText::FromString(FString(TEXT("Empty"))));
	}
}
