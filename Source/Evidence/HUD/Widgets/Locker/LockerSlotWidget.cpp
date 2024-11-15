// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSlotWidget.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment.h"

void ULockerSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot(nullptr);
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
