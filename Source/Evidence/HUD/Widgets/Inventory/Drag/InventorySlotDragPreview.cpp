// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotDragPreview.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

void UInventorySlotDragPreview::NativeConstruct()
{
	Super::NativeConstruct();

	AEquipment* const Equipment = InventoryComponent->GetEquipmentAtIndex(Index);
	if (Equipment)
	{
		SlotText->SetText(FText::FromString(Equipment->GetEquipmentName()));
	}
	else
	{
		SlotText->SetText(FText::FromString(TEXT("Empty")));
	}
}

void UInventorySlotDragPreview::SetIndex(const uint8 NewIndex)
{
	Index = NewIndex;
}

void UInventorySlotDragPreview::SetInventoryComponent(UInventoryManagerComponent* Comp)
{
	InventoryComponent = Comp;
}

void UInventorySlotDragPreview::SetColour(const FColor Colour)
{
	SlotText->SetColorAndOpacity(FSlateColor(Colour));
}
