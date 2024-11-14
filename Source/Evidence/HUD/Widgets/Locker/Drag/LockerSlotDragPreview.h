// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockerSlotDragPreview.generated.h"

class ALocker;
class UTextBlock;

/**
 *  Cosmetic widget that is displayed when ULockerSlotDragDropOperation is dragged
 */
UCLASS()
class EVIDENCE_API ULockerSlotDragPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 NewIndex);
	void SetLocker(ALocker* NewLocker);
	void SetColour(const FColor Colour);

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText;

	uint8 Index;

	UPROPERTY()
	ALocker* Locker;
	
};
