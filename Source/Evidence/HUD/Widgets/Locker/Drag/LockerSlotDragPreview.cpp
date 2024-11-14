// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSlotDragPreview.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Hub/Locker.h"

void ULockerSlotDragPreview::NativeConstruct()
{
	Super::NativeConstruct();

	AEquipment* const Equipment = Locker->GetEquipmentAtIndex(Index);
	if (Equipment)
	{
		SlotText->SetText(FText::FromString(Equipment->GetEquipmentName()));
	}
	else
	{
		SlotText->SetText(FText::FromString(TEXT("Empty")));
	}
}

void ULockerSlotDragPreview::SetIndex(const uint8 NewIndex)
{
	Index = NewIndex;
}

void ULockerSlotDragPreview::SetLocker(ALocker* NewLocker)
{
	Locker = NewLocker;
}

void ULockerSlotDragPreview::SetColour(const FColor Colour)
{
	SlotText->SetColorAndOpacity(FSlateColor(Colour));
}
