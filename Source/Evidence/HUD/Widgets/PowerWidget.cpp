// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/PoweredEquipment.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UPowerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		UInventoryComponent* InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			APoweredEquipment* Powered = Cast<APoweredEquipment>(InventoryComponent->GetEquipped());

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
	}
}

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
