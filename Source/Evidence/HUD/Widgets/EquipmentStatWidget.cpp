// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStatWidget.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UEquipmentStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayer())
	{
		if (GetOwningPlayer()->GetCharacter())
		{
			SetupDelegate(nullptr, GetOwningPlayer()->GetCharacter());
		}
		else
		{
			GetOwningPlayer()->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::SetupDelegate);
		}
	}
}

void UEquipmentStatWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
}

void UEquipmentStatWidget::EquipmentSetup(UInventoryComponent* const InventoryComponent)
{
}

void UEquipmentStatWidget::SetupDelegate(APawn* OldPawn, APawn* NewPawn)
{
	const AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(NewPawn);
	if (Char)
	{
		UInventoryComponent* const InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			EquipmentSetup(InventoryComponent);
			InventoryComponent->EquippedChanged.AddUObject(this, &ThisClass::OnEquippedChanged);
		}
	}
}
