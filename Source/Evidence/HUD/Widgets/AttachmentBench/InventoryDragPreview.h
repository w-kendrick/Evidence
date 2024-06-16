// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDragPreview.generated.h"

class UTextBlock;
class UInventoryComponent;

UCLASS()
class EVIDENCE_API UInventoryDragPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 NewIndex);
	void SetInventoryComponent(UInventoryComponent* Comp);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText;

	uint8 Index;
	UInventoryComponent* InventoryComponent;
	
};
