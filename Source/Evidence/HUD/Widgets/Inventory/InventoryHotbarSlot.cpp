// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHotbarSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Evidence/Items/Equipment.h"

void UInventoryHotbarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot(nullptr);
	SelectSlot(false);
}

void UInventoryHotbarSlot::UpdateSlot(const AEquipment* const Equipment)
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

void UInventoryHotbarSlot::SelectSlot(const bool Status)
{
	SelectedBorder->SetVisibility(Status ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
