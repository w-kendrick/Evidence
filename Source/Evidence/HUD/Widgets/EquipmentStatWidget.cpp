// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStatWidget.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UEquipmentStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		UInventoryComponent* InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			InventoryComponent->EquippedChanged.AddUObject(this, &ThisClass::OnEquippedChanged);
		}
	}
}

void UEquipmentStatWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
}
