// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragPreview.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UInventoryDragPreview::NativeConstruct()
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

void UInventoryDragPreview::SetIndex(const uint8 NewIndex)
{
	Index = NewIndex;
}

void UInventoryDragPreview::SetInventoryComponent(UInventoryComponent* Comp)
{
	InventoryComponent = Comp;
}
