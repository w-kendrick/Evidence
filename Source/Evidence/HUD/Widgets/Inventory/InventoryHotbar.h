// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Structs/EquipmentList.h"
#include "InventoryHotbar.generated.h"

class UInventoryHotbarSlot;

/**
Widget for showing the equipment stored in player inventory
 */
UCLASS()
class EVIDENCE_API UInventoryHotbar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* Hotbar;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryHotbarSlot> SlotClass;

	UPROPERTY()
	TArray<UInventoryHotbarSlot*> HotbarSlots;

private:
	UFUNCTION()
	void SetupDelegate(APawn* OldPawn, APawn* NewPawn);

	void InitializeSlots();

	void OnInventoryChanged(FEquipmentList EquipmentList);
	virtual void OnEquippedIndexChanged(uint8 SelectedIndex, uint8 PrevIndex);
	
};
