// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerWidget.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"

void UPowerWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	APoweredEquipment* PrevPowered = Cast<APoweredEquipment>(Previous);
	if (PrevPowered)
	{
		PrevPowered->OnPowerChanged.Remove(PoweredHandle);
	}

	APoweredEquipment* Powered = Cast<APoweredEquipment>(Current);

	if (Powered)
	{
		PoweredHandle = Powered->OnPowerChanged.AddUObject(this, &ThisClass::OnPowerChanged);
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPowerWidget::OnPowerChanged(float Power, float MaxPower)
{
}
