// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/DisableInputWidget.h"
#include "LockerWidget.generated.h"

struct FEquipmentList;
class ULockerSlotWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ULockerWidget : public UDisableInputWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void LeaveEvent() override;

private:
	void InitializeSlots();
	void OnLockerStorageChanged(const FEquipmentList& EquipmentList);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULockerSlotWidget> SlotClass;

	UPROPERTY()
	TArray<ULockerSlotWidget*> LockerSlots;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* LockerRows;
	
};
