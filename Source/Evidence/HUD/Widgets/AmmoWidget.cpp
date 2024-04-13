// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/Gun.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		UInventoryComponent* InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			AGun* Gun = Cast<AGun>(InventoryComponent->GetEquipped());

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
	}
}

void UAmmoWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	AGun* PrevGun = Cast<AGun>(Previous);
	if (PrevGun)
	{
		PrevGun->OnAmmoChanged.Remove(GunHandle);
	}

	AGun* Gun = Cast<AGun>(Current);

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

void UAmmoWidget::OnAmmoChanged(uint8 Ammo)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(Ammo)));
}
