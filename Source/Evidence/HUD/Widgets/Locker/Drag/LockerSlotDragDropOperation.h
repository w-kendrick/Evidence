// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "LockerSlotDragDropOperation.generated.h"

class ALocker;
class ULockerSlotWidget;

/**
 * Stores information of locker slot that is dragged and dropped
 */
UCLASS()
class EVIDENCE_API ULockerSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const uint8 NewIndex, ALocker* NewLocker, ULockerSlotWidget* Source);
	uint8 GetIndex() const { return Index; }
	ALocker* GetLocker() const { return Locker; }
	ULockerSlotWidget* GetWidgetSource() const { return WidgetSource; }

protected:
	uint8 Index;

	UPROPERTY()
	ALocker* Locker;

	UPROPERTY()
	ULockerSlotWidget* WidgetSource;
	
};
