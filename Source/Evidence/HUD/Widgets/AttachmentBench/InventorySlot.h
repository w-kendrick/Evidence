// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UInventoryDragPreview;
class UDragWidget;

UCLASS()
class EVIDENCE_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryDragPreview> DragPreviewClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDragWidget> DragWidgetClass;
};
