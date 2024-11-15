// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockerSlotWidget.generated.h"

class AEquipment;

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

private:
	uint8 StorageIndex;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
	
};
