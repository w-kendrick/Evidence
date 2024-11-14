// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotDragDropOperation.h"

void UInventorySlotDragDropOperation::SpawnInitialize(const uint8 NewIndex, UInventoryManagerComponent* Comp)
{
	Index = NewIndex;
	InventoryComponent = Comp;
}
