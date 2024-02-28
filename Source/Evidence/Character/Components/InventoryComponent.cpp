// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Character/EvidenceCharacter.h"

#pragma region Class Essentials

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Char = Cast<AEvidenceCharacter>(GetOwner());
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Equipped);
}

#pragma endregion

#pragma region Rep Notifies

void UInventoryComponent::OnRep_Equipped(AEquipment* PrevEquipped)
{
	if (PrevEquipped)
	{
		PrevEquipped->Drop();
	}

	if (Equipped && Char)
	{
		Equipped->Pickup(Char);
	}
}

void UInventoryComponent::OnRep_Inventory(TArray<EEquipmentID> NewInventory)
{

}

#pragma endregion

#pragma region Equipped

void UInventoryComponent::PickupEquipped(AEquipment* NewEquipped)
{
	if (Equipped)
	{
		Equipped->Drop();
	}

	Equipped = NewEquipped;

	if (Equipped && Char)
	{
		Equipped->Pickup(Char);
	}
}

void UInventoryComponent::DropEquipped()
{
	if (Equipped)
	{
		Equipped->Drop();
	}

	Equipped = nullptr;
}

#pragma endregion

#pragma region Inventory

void UInventoryComponent::PickupToInventory(AEquipment* NewEquipped)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Pickup to inventory");
	SetInventoryIndex(EEquipmentID::Test1, 0);
}

void UInventoryComponent::SetInventoryIndex(const EEquipmentID ID, const uint8 Index)
{
	Inventory[Index] = ID;
	Inventory = Inventory; //forces rep notify to be called
}

#pragma endregion