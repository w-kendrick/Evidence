// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/Button.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UInventorySlotWidget::ButtonLeftClicked()
{
	if (InventoryComp)
	{
		InventoryComp->TryEquipFromInventory(Index);
	}
}

void UInventorySlotWidget::ButtonRightClicked()
{
	if (InventoryComp)
	{
		InventoryComp->TryDropFromInventory(Index);
	}
}

void UInventorySlotWidget::SpawnInitialize(UInventoryComponent* Comp, AEquipment* NewEquipment, const uint8 InventoryIndex)
{
	InventoryComp = Comp;
	Equipment = NewEquipment;
	Index = InventoryIndex;
}
