// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragWidget.generated.h"

class UInventoryManagerComponent;

UCLASS()
class EVIDENCE_API UInventoryDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const uint8 NewIndex, UInventoryManagerComponent* Comp);
	uint8 GetIndex() const;
	UInventoryManagerComponent* GetInventoryComponent() const;
	
protected:
	uint8 Index;

	UPROPERTY()
	UInventoryManagerComponent* InventoryComponent;
};
