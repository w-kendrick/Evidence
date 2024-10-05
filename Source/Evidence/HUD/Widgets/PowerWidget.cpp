// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/PowerEquipment.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Items/Equipment.h"

void UPowerWidget::EquipmentSetup(UInventoryManagerComponent* const InventoryComponent)
{
	const APowerEquipment* const Powered = Cast<APowerEquipment>(InventoryComponent->GetEquipped());

	if (Powered)
	{
		PowerBar->SetPercent(Powered->GetPower() / Powered->GetMaxPower());
		PowerText->SetText(FText::FromString(FString::FromInt(Powered->GetPower())));
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPowerWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	APowerEquipment* const PrevPowered = Cast<APowerEquipment>(Previous);
	if (PrevPowered)
	{
		PrevPowered->OnPowerChanged.Remove(PoweredHandle);
	}

	APowerEquipment* const Powered = Cast<APowerEquipment>(Current);

	if (Powered)
	{
		PoweredHandle = Powered->OnPowerChanged.AddUObject(this, &ThisClass::OnPowerChanged);
		SetVisibility(ESlateVisibility::Visible);
		PowerBar->SetPercent(Powered->GetPower() / Powered->GetMaxPower());
		PowerText->SetText(FText::FromString(FString::FromInt(Powered->GetPower())));
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPowerWidget::OnPowerChanged(float Power, float MaxPower)
{
	PowerBar->SetPercent(Power / MaxPower);
	PowerText->SetText(FText::FromString(FString::SanitizeFloat(Power)));
}
