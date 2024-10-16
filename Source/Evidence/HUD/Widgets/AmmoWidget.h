// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStatWidget.h"
#include "AmmoWidget.generated.h"

class UInventoryManagerComponent;

UCLASS()
class EVIDENCE_API UAmmoWidget : public UEquipmentStatWidget
{
	GENERATED_BODY()

protected:
	virtual void EquipmentSetup(UInventoryManagerComponent* const InventoryComponent) override;
	virtual void OnEquippedChanged(AEquipment* Current, AEquipment* Previous) override;
	void OnAmmoChanged(uint8 Ammo);

	FDelegateHandle AmmoHandle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;
	
};
