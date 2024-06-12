// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragPreview.h"
#include "Components/TextBlock.h"

void UInventoryDragPreview::NativeConstruct()
{
	Super::NativeConstruct();

	SlotText->SetText(FText::FromString(FString::FromInt(Index)));
}

void UInventoryDragPreview::SetIndex(const uint8 NewIndex)
{
	Index = NewIndex;
}
