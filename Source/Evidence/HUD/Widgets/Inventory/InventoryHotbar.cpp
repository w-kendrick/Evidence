// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHotbar.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Structs/EquipmentList.h"
#include "Evidence/HUD/Widgets/Inventory/InventoryHotbarSlot.h"
#include "Components/HorizontalBox.h"

void UInventoryHotbar::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeSlots();

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
	const ABaseCharacter* const Char = Cast<ABaseCharacter>(NewPawn);
	if (Char)
	{
		UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();
		if (InventoryComponent)
		{
			InventoryComponent->OnInventoryChanged.AddUObject(this, &ThisClass::OnInventoryChanged);
			InventoryComponent->OnEquippedIndexChanged.AddUObject(this, &ThisClass::OnEquippedIndexChanged);
		}
	}
}

void UInventoryHotbar::InitializeSlots()
{
	for (uint8 Index = 0; Index < INVENTORY_SIZE; Index++)
	{
		UInventoryHotbarSlot* const InventorySlot = CreateWidget<UInventoryHotbarSlot>(this, SlotClass);
		Hotbar->AddChild(InventorySlot);
		HotbarSlots.Add(InventorySlot);
	}
}

void UInventoryHotbar::OnInventoryChanged(FEquipmentList EquipmentList)
{
	for (uint8 Index = 0; Index < INVENTORY_SIZE; Index++)
	{
		const AEquipment* const Equipment = EquipmentList[Index].GetEquipment();
		HotbarSlots[Index]->UpdateSlot(Equipment);
	}
}

void UInventoryHotbar::OnEquippedIndexChanged(uint8 SelectedIndex, uint8 PrevIndex)
{
	HotbarSlots[PrevIndex]->SelectSlot(false);
	HotbarSlots[SelectedIndex]->SelectSlot(true);
}
