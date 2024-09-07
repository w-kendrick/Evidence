// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHotbarSlot.h"

void UInventoryHotbarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateSlot(nullptr);
}

void UInventoryHotbarSlot::UpdateSlot(const AEquipment* const Equipment)
{
	if (Equipment)
	{

	}
	else
	{

	}
}
