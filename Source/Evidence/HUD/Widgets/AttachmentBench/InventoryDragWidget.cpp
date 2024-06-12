// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragWidget.h"

void UInventoryDragWidget::SetIndex(const uint8 NewIndex)
{
	Index = NewIndex;
}

uint8 UInventoryDragWidget::GetIndex() const
{
	return Index;
}
