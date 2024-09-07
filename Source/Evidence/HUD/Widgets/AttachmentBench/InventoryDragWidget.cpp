// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragWidget.h"

void UInventoryDragWidget::SpawnInitialize(const uint8 NewIndex, UInventoryManagerComponent* Comp)
{
	Index = NewIndex;
	InventoryComponent = Comp;
}

uint8 UInventoryDragWidget::GetIndex() const
{
	return Index;
}

UInventoryManagerComponent* UInventoryDragWidget::GetInventoryComponent() const
{
	return InventoryComponent;
}
