// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/Ammunition/Ammunition.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

void UAmmoWidget::EquipmentSetup(UInventoryManagerComponent* const InventoryComponent)
{
	const AAmmunition* const Ammo = Cast<AAmmunition>(InventoryComponent->GetEquipped());

	if (Ammo)
	{
		AmmoText->SetText(FText::FromString(FString::FromInt(Ammo->GetQuantity())));
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAmmoWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	AAmmunition* const PrevAmmo = Cast<AAmmunition>(Previous);
	if (PrevAmmo)
	{
		PrevAmmo->OnQuantityChanged.Remove(AmmoHandle);
	}

	AAmmunition* const Ammo = Cast<AAmmunition>(Current);

	if (Ammo)
	{
		AmmoHandle = Ammo->OnQuantityChanged.AddUObject(this, &ThisClass::OnAmmoChanged);
		SetVisibility(ESlateVisibility::Visible);
		AmmoText->SetText(FText::FromString(FString::FromInt(Ammo->GetQuantity())));
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAmmoWidget::OnAmmoChanged(uint8 Ammo)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(Ammo)));
}
