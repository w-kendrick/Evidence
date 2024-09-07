// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStatWidget.h"
#include "PowerWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UPowerWidget : public UEquipmentStatWidget
{
	GENERATED_BODY()

protected:
	virtual void EquipmentSetup(UInventoryManagerComponent* const InventoryComponent) override;
	virtual void OnEquippedChanged(AEquipment* Current, AEquipment* Previous) override;
	void OnPowerChanged(float Power, float MaxPower);

	FDelegateHandle PoweredHandle;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PowerBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PowerText;
	
};
