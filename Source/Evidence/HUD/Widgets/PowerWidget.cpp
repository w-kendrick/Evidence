// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Items/Equipment.h"

void UPowerWidget::EquipmentSetup(UInventoryManagerComponent* const InventoryComponent)
{
	const IPowerInterface* const Powered = Cast<IPowerInterface>(InventoryComponent->GetEquipped());

	if (Powered)
	{
		PowerBar->SetPercent(Powered->GetPowerComponent()->GetPower() / Powered->GetPowerComponent()->GetMaxPower());
		PowerText->SetText(FText::FromString(FString::FromInt(Powered->GetPowerComponent()->GetPower())));
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPowerWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	IPowerInterface* const PrevPowered = Cast<IPowerInterface>(Previous);
	if (PrevPowered)
	{
		PrevPowered->GetPowerComponent()->OnPowerChanged.Remove(PoweredHandle);
	}

	IPowerInterface* const Powered = Cast<IPowerInterface>(Current);

	if (Powered)
	{
		PoweredHandle = Powered->GetPowerComponent()->OnPowerChanged.AddUObject(this, &ThisClass::OnPowerChanged);
		SetVisibility(ESlateVisibility::Visible);
		PowerBar->SetPercent(Powered->GetPowerComponent()->GetPower() / Powered->GetPowerComponent()->GetMaxPower());
		PowerText->SetText(FText::FromString(FString::FromInt(Powered->GetPowerComponent()->GetPower())));
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
