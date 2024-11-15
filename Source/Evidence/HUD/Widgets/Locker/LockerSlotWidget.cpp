// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Hub/Locker.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragPreview.h"
#include "Evidence/HUD/Widgets/Locker/Drag/LockerSlotDragDropOperation.h"

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
