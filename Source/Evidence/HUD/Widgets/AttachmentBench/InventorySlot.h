// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UInventoryDragPreview;
class UInventoryDragWidget;
class UTextBlock;
class UInventoryComponent;

UCLASS()
class EVIDENCE_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const uint8 Index, UInventoryComponent* Comp);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	uint8 InventoryIndex;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryDragPreview> DragPreviewClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryDragWidget> DragWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText;
};
