// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragWidget.h"
#include "InventoryDragPreview.h"

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}

	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UInventoryDragPreview* DragPreview = CreateWidget<UInventoryDragPreview>(this, DragPreviewClass);

	UDragWidget* DragWidget = Cast<UDragWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragWidgetClass));
	DragWidget->DefaultDragVisual = DragPreview;
	DragWidget->Pivot = EDragPivot::MouseDown;

	OutOperation = DragWidget;
}