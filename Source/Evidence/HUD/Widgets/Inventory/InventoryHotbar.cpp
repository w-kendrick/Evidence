// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHotbar.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

void UInventoryHotbar::NativeConstruct()
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

void UInventoryHotbar::SetupDelegate(APawn* OldPawn, APawn* NewPawn)
{
	const AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(NewPawn);
	if (Char)
	{
		UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			InventoryComponent->OnInventoryChanged.AddUObject(this, &ThisClass::OnInventoryChanged);
		}
	}
}

void UInventoryHotbar::OnInventoryChanged(FEquipmentList EquipmentList)
{
}
