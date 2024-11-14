// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHotbarSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Items/Equipment.h"

void UInventoryHotbarSlot::NativeConstruct()
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

	UpdateSlot(nullptr);
	SelectSlot(false);
}

void UInventoryHotbarSlot::SetIndex(const uint8 Index)
{
	InventoryIndex = Index;
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
