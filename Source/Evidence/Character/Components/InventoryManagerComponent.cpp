// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Items/Equipment/Ammunition/Ammunition.h"

UInventoryManagerComponent::UInventoryManagerComponent()
	: EquipmentList(INVENTORY_SIZE)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryManagerComponent::Pickup(AEquipment* const Equipment)
{
	Pickup(Equipment, SelectedIndex);
}

void UInventoryManagerComponent::Pickup(AEquipment* const Equipment, const uint8 Index)
{
	AEquipment* const PrevEquipped = GetEquipped();

	EquipmentList.AddEntry(Equipment, Index);
	OnInventoryChanged.Broadcast(EquipmentList);

	if (Index == SelectedIndex)
	{
		UpdateEquipped(PrevEquipped, EUnequipType::Drop);
	}
	else if (Equipment)
	{
		Equipment->Stow(CharacterOwner);
	}
}

void UInventoryManagerComponent::Drop(const uint8 Index)
{
	EquipmentList.RemoveEntry(Index);
	OnInventoryChanged.Broadcast(EquipmentList);
}

void UInventoryManagerComponent::DropEquipped()
{
	AEquipment* const PrevEquipped = GetEquipped();

	Drop(SelectedIndex);

	UpdateEquipped(PrevEquipped, EUnequipType::Drop);
}

void UInventoryManagerComponent::DropInventory()
{
	AEquipment* const PrevEquipped = GetEquipped();

	for (uint8 Index = 0; Index < INVENTORY_SIZE; Index++)
	{
		Drop(Index);
	}

	UpdateEquipped(PrevEquipped, EUnequipType::Drop);
}

const FEquipmentList& UInventoryManagerComponent::GetInventory() const
{
	return EquipmentList;
}

AEquipment* UInventoryManagerComponent::GetEquipmentAtIndex(const uint8 Index) const
{
	return EquipmentList[Index].GetEquipment();
}

AEquipment* UInventoryManagerComponent::GetEquipped() const
{
	return GetEquipmentAtIndex(SelectedIndex);
}

bool UInventoryManagerComponent::IsAmmoAvailable(const TSubclassOf<AAmmunition>& AmmoType) const
{
	bool Result = false;

	for (uint8 i = 0; i < INVENTORY_SIZE; i++)
	{
		const AEquipment* const Equipment = GetEquipmentAtIndex(i);
		if (Equipment && Equipment->GetClass() == AmmoType)
		{
			Result = true;
		}
	}

	return Result;
}

uint8 UInventoryManagerComponent::ConsumeAmmo(const TSubclassOf<AAmmunition> AmmoType, const uint8 Required)
{
	uint8 Amount = 0;

	for (uint8 Index = 0; Index < INVENTORY_SIZE; ++Index)
	{
		AEquipment* const Equipment = GetEquipmentAtIndex(Index);
		if (Equipment && Equipment->GetClass() == AmmoType)
		{
			bool isSlotExhausted = false;
			AAmmunition* const Ammunition = Cast<AAmmunition>(Equipment);

			const uint8 QuantityToTake = FMath::Clamp(Ammunition->GetQuantity(), 0, Required - Amount);
			Ammunition->Consume(QuantityToTake, isSlotExhausted);
			Amount += QuantityToTake;

			if (isSlotExhausted)
			{
				Drop(Index);
				Equipment->Destroy();
			}
		}
	}

	return Amount;
}

void UInventoryManagerComponent::IncrementSelectedIndex()
{
	SetSelectedIndex((SelectedIndex + 1) % INVENTORY_SIZE);
}

void UInventoryManagerComponent::DecrementSelectedIndex()
{
	if (SelectedIndex == 0)
	{
		SetSelectedIndex(INVENTORY_SIZE - 1);
	}
	else
	{
		SetSelectedIndex(SelectedIndex - 1);
	}
}

void UInventoryManagerComponent::SetSelectedIndex(const uint8 Index)
{
	const uint8 PrevIndex = SelectedIndex;

	SelectedIndex = Index;

	OnEquippedIndexChanged.Broadcast(SelectedIndex, PrevIndex);
	UpdateEquipped(EquipmentList[PrevIndex].GetEquipment(), EUnequipType::Stow);
}

void UInventoryManagerComponent::UpdateEquipped(AEquipment* const PrevEquipped, const EUnequipType Type)
{
	AEquipment* const Equipped = GetEquipped();
	if (Equipped)
	{
		Equipped->Pickup(CharacterOwner);
	}

	if (PrevEquipped)
	{
		switch (Type)
		{
		case EUnequipType::Stow:
			PrevEquipped->Stow(CharacterOwner);
			break;
		case EUnequipType::Drop:
			PrevEquipped->Drop();
			break;
		}
	}

	OnEquippedChanged.Broadcast(GetEquipped(), PrevEquipped);
}

void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ABaseCharacter>(GetOwner());

	OnInventoryChanged.Broadcast(EquipmentList);
	OnEquippedIndexChanged.Broadcast(SelectedIndex, 0);
	OnEquippedChanged.Broadcast(GetEquipped(), nullptr);
}

void UInventoryManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryManagerComponent, EquipmentList);
	DOREPLIFETIME(UInventoryManagerComponent, SelectedIndex);
}

void UInventoryManagerComponent::OnRep_EquipmentList(const FEquipmentList PrevList)
{
	OnInventoryChanged.Broadcast(EquipmentList);

	if (PrevList[SelectedIndex] != EquipmentList[SelectedIndex])
	{
		UpdateEquipped(PrevList[SelectedIndex].GetEquipment(), EUnequipType::Drop);
	}
}

void UInventoryManagerComponent::OnRep_SelectedIndex(const uint8 PrevIndex)
{
	UpdateEquipped(GetEquipmentAtIndex(PrevIndex), EUnequipType::Stow);
	OnEquippedIndexChanged.Broadcast(SelectedIndex, PrevIndex);
}
