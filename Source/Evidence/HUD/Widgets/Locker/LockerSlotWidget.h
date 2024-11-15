// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockerSlotWidget.generated.h"

class AEquipment;
class ALocker;
class ULockerSlotDragPreview;
class ULockerSlotDragDropOperation;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ULockerSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 NewIndex);

	void UpdateSlot(const AEquipment* const Equipment);

protected:
	void NativeConstruct() override;
	FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	uint8 StorageIndex;

	UPROPERTY()
	ALocker* Locker;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULockerSlotDragPreview> DragPreviewClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULockerSlotDragDropOperation> DragOperationClass;
	
};
