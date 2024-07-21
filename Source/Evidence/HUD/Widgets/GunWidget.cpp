// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWidget.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/Gun.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

void UGunWidget::EquipmentSetup(UInventoryManagerComponent* const InventoryComponent)
{
	const AGun* const Gun = Cast<AGun>(InventoryComponent->GetEquipped());

	if (Gun)
	{
		AmmoText->SetText(FText::FromString(FString::FromInt(Gun->GetCurrentClip())));
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGunWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	AGun* const PrevGun = Cast<AGun>(Previous);
	if (PrevGun)
	{
		PrevGun->OnAmmoChanged.Remove(GunHandle);
	}

	AGun* const Gun = Cast<AGun>(Current);

	if (Gun)
	{
		GunHandle = Gun->OnAmmoChanged.AddUObject(this, &ThisClass::OnAmmoChanged);
		SetVisibility(ESlateVisibility::Visible);
		AmmoText->SetText(FText::FromString(FString::FromInt(Gun->GetCurrentClip())));
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGunWidget::OnAmmoChanged(uint8 Ammo)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(Ammo)));
}
