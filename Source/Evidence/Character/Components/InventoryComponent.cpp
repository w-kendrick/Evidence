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

void UInventoryComponent::PickupToInventory(AEquipment* NewEquipped)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Pickup to inventory");
}
