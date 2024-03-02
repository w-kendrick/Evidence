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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Left click");
	if (InventoryComp)
	{
		InventoryComp->EquipFromInventory(Index);
	}
}

void UInventorySlotWidget::ButtonRightClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Right click");
	if (InventoryComp)
	{
		InventoryComp->DropFromInventory(Index);
	}
}

void UInventorySlotWidget::SpawnInitialize(UInventoryComponent* Comp, const EEquipmentID Object, const uint8 InventoryIndex)
{
	InventoryComp = Comp;
	Slot = Object;
	Index = InventoryIndex;
}
