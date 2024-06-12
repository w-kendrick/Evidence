// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragWidget.generated.h"

UCLASS()
class EVIDENCE_API UInventoryDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 NewIndex);
	uint8 GetIndex() const;
	
protected:
	uint8 Index;
};
