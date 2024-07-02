// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStatWidget.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

static constexpr float SETUP_PERIOD = 0.5f;

void UEquipmentStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		UInventoryComponent* const InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			EquipmentSetup(InventoryComponent);
			InventoryComponent->EquippedChanged.AddUObject(this, &ThisClass::OnEquippedChanged);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(SetupHandle, this, &ThisClass::ReattemptSetup, SETUP_PERIOD, true);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SetupHandle, this, &ThisClass::ReattemptSetup, SETUP_PERIOD, true);
	}
}

void UEquipmentStatWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
}

void UEquipmentStatWidget::EquipmentSetup(UInventoryComponent* const InventoryComponent)
{
}

void UEquipmentStatWidget::ReattemptSetup()
{
	const AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		UInventoryComponent* const InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			EquipmentSetup(InventoryComponent);
			InventoryComponent->EquippedChanged.AddUObject(this, &ThisClass::OnEquippedChanged);

			GetWorld()->GetTimerManager().ClearTimer(SetupHandle);
		}
	}
}
