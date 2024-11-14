// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotDragPreview.generated.h"

class UTextBlock;
class UInventoryManagerComponent;

/**
 * Cosmetic widget that is displayed when UInventorySlotDragDropOperation is dragged
 */
UCLASS()
class EVIDENCE_API UInventorySlotDragPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 NewIndex);
	void SetInventoryComponent(UInventoryManagerComponent* Comp);
	void SetColour(const FColor Colour);

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText;

	uint8 Index;

	UPROPERTY()
	UInventoryManagerComponent* InventoryComponent;
	
};
