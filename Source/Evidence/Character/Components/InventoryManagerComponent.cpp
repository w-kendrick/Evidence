// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Items/Equipment/Ammunition/Ammunition.h"

UInventoryManagerComponent::UInventoryManagerComponent()
	: EquipmentList(GetOwner())
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryManagerComponent::Pickup(AEquipment* const Equipment)
{
	AEquipment* const PrevEquipped = GetEquipped();

	Pickup(Equipment, SelectedIndex);

	if (!CharacterOwner)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Invalid character owner");
		return;
	}

	if (Equipment)
	{
		Equipment->Pickup(CharacterOwner);
	}

	OnEquippedChanged.Broadcast(GetEquipped(), PrevEquipped);
}

void UInventoryManagerComponent::Pickup(AEquipment* const Equipment, const uint8 Index)
{
	EquipmentList.AddEntry(Equipment, Index);
	OnInventoryChanged.Broadcast(EquipmentList);
}

void UInventoryManagerComponent::Drop(const uint8 Index)
{
	EquipmentList.RemoveEntry(Index);
	OnInventoryChanged.Broadcast(EquipmentList);
}

void UInventoryManagerComponent::DropEquipped()
{
	Drop(SelectedIndex);
}

const FEquipmentList& UInventoryManagerComponent::GetInventory() const
{
	return EquipmentList;
}

AEquipment* UInventoryManagerComponent::GetEquipmentAtIndex(const uint8 Index) const
{
	return EquipmentList[Index].GetEquipment();;
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
	const uint8 PrevIndex = SelectedIndex;
	SelectedIndex = (SelectedIndex + 1) % INVENTORY_SIZE;

	OnEquippedIndexChanged.Broadcast(SelectedIndex, PrevIndex);
}

void UInventoryManagerComponent::DecrementSelectedIndex()
{
	const uint8 PrevIndex = SelectedIndex;

	if (SelectedIndex == 0)
	{
		SelectedIndex = INVENTORY_SIZE - 1;
	}
	else
	{
		SelectedIndex -= 1;
	}

	OnEquippedIndexChanged.Broadcast(SelectedIndex, PrevIndex);
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
		OnEquippedChanged.Broadcast(GetEquipped(), PrevList[SelectedIndex].GetEquipment());
	}
}

void UInventoryManagerComponent::OnRep_SelectedIndex(const uint8 PrevIndex)
{
	OnEquippedChanged.Broadcast(GetEquipped(), GetEquipmentAtIndex(PrevIndex));
	OnEquippedIndexChanged.Broadcast(SelectedIndex, PrevIndex);
}
