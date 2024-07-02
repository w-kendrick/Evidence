// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStatWidget.h"
#include "GunWidget.generated.h"

class AEquipment;
class UInventoryComponent;

UCLASS()
class EVIDENCE_API UGunWidget : public UEquipmentStatWidget
{
	GENERATED_BODY()

protected:
	virtual void EquipmentSetup(UInventoryComponent* const InventoryComponent) override;
	virtual void OnEquippedChanged(AEquipment* Current, AEquipment* Previous) override;
	void OnAmmoChanged(uint8 Ammo);

	FDelegateHandle GunHandle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;

};
