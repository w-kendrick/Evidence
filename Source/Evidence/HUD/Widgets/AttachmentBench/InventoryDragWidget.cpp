// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragWidget.h"

void UInventoryDragWidget::SpawnInitialize(const uint8 NewIndex, UInventoryComponent* Comp)
{
	Index = NewIndex;
	InventoryComponent = Comp;
}

uint8 UInventoryDragWidget::GetIndex() const
{
	return Index;
}

UInventoryComponent* UInventoryDragWidget::GetInventoryComponent() const
{
	return InventoryComponent;
}
