// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Net/UnrealNetwork.h"

#pragma region Class Essentials

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Equipped);
}

#pragma endregion

void UInventoryComponent::OnRep_Equipped(AEquipment* PrevEquipped)
{
	if (PrevEquipped)
	{
		PrevEquipped->Drop();
	}

	if (Equipped)
	{
		Equipped->Pickup(Char);
	}
}

void UInventoryComponent::PickupEquipped(AEquipment* NewEquipped)
{
	Equipped = NewEquipped;
}

void UInventoryComponent::DropEquipped()
{
	Equipped = nullptr;
}

void UInventoryComponent::PickupToInventory(AEquipment* NewEquipped)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Pickup to inventory");
}
