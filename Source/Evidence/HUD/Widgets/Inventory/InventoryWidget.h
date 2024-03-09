// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Enums/EquipmentID.h"
#include "InventoryWidget.generated.h"

UCLASS()
class EVIDENCE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInventoryComp(class UInventoryComponent* Comp);
	void Update();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInventorySlotWidget> SlotClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEquipmentWidget> EquippedClass;

	UPROPERTY(EditDefaultsOnly)
	uint8 Rows;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* InventoryBox;

	UPROPERTY(meta = (BindWidget))
	class UBorder* EquippedBox;

	void OnInventoryChanged();
	void OnEquippedChanged();

private:
	UPROPERTY()
	UInventoryComponent* InventoryComp;
	UPROPERTY()
	TArray<UEquipmentWidget*> InventorySlots;
};
