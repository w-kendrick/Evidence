// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#pragma region Class Essentials

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	Inventory.SetNum(10);
	InitializeInventory();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Char = Cast<AEvidenceCharacter>(GetOwner());
	EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
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

#pragma region Pickup

void UInventoryComponent::Pickup(AEquipment* Equipment)
{
	if (Equipped)
	{
		uint8 Index;
		if (DetermineFreeSpot(Index))
		{
			PickupToInventory(Equipment, Index);
		}
		else
		{
			DropEquipped();
			PickupEquipped(Equipment);
		}
	}
	else
	{
		PickupEquipped(Equipment);
	}
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

void UInventoryComponent::EquipFromInventory(const uint8 Index)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Equip from inventory");

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Char, FGameplayTag::RequestGameplayTag(FName("Ability.EquipFromInventory")), Payload);
}

EEquipmentID UInventoryComponent::GetEquippedType() const
{
	if (Equipped)
	{
		return EGS->GetEquipmentID(Equipped->GetClass());
	}
	else
	{
		return EEquipmentID::Empty;
	}
}

#pragma endregion

#pragma region Inventory

void UInventoryComponent::PickupToInventory(AEquipment* NewEquipped, const uint8 Index)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Pickup to inventory");
}

void UInventoryComponent::DropFromInventory(const uint8 Index)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Drop from inventory");
}

void UInventoryComponent::ToggleInventoryWidget() const
{
	InventoryRequest.Broadcast();
}

const TArray<EEquipmentID>& UInventoryComponent::GetInventory() const
{
	return Inventory;
}

void UInventoryComponent::SetInventoryIndex(const EEquipmentID ID, const uint8 Index)
{
	Inventory[Index] = ID;
	Inventory = Inventory; //forces rep notify to be called
}

#pragma endregion

#pragma region Helper Functions

bool UInventoryComponent::DetermineFreeSpot(uint8& Index) const
{
	bool result = false;

	for (uint8 i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i] == EEquipmentID::Empty)
		{
			Index = i;
			return true;
		}
	}
	return false;
}

void UInventoryComponent::InitializeInventory()
{
	for (uint8 i = 0; i < Inventory.Num(); ++i)
	{
		Inventory[i] = EEquipmentID::Empty;
	}
}

#pragma endregion