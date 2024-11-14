// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHotbarSlot.generated.h"

class AEquipment;
class UInventoryManagerComponent;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UInventoryHotbarSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIndex(const uint8 Index);

	void UpdateSlot(const AEquipment* const Equipment);

	void SelectSlot(const bool Status);

protected:
	void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectedBorder;

	UPROPERTY()
	UInventoryManagerComponent* InventoryComponent;

	uint8 InventoryIndex;
};
