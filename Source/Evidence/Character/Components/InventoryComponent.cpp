// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
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
	DOREPLIFETIME(UInventoryComponent, Inventory);
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

	EquippedChanged.Broadcast();
}

void UInventoryComponent::OnRep_Inventory(TArray<AEquipment*> NewInventory)
{
	InventoryChanged.Broadcast();
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
	EquippedChanged.Broadcast();

	if (Equipped && Char)
	{
		Equipped->Pickup(Char);
	}
}

void UInventoryComponent::TryDropEquipped()
{
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Char, FGameplayTag::RequestGameplayTag(FName("Ability.Drop")), Payload);
}

void UInventoryComponent::DropEquipped()
{
	if (Equipped)
	{
		Equipped->Drop();
	}

	Equipped = nullptr;
	EquippedChanged.Broadcast();
}

void UInventoryComponent::TryEquipFromInventory_Implementation(const uint8 Index)
{
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Char, FGameplayTag::RequestGameplayTag(FName("Ability.EquipFromInventory")), Payload);
}

void UInventoryComponent::EquipFromInventory(const int Index)
{
	AEquipment* Equipment = Inventory[Index];

	PickupToInventory(Equipped, Index);

	PickupEquipped(Equipment);
}

#pragma endregion

#pragma region Inventory

void UInventoryComponent::PickupToInventory(AEquipment* Equipment, const uint8 Index)
{
	SetInventoryIndex(Equipment, Index);

	if (Equipment)
	{
		Equipment->Attach(Char, false);
	}
}

void UInventoryComponent::TryDropFromInventory_Implementation(const uint8 Index)
{
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Char, FGameplayTag::RequestGameplayTag(FName("Ability.DropFromInventory")), Payload);
}

void UInventoryComponent::DropFromInventory(const int Index)
{
	AEquipment* Equipment = Inventory[Index];

	if (Equipment)
	{
		Equipment->Drop();
		SetInventoryIndex(nullptr, Index);
	}
}

void UInventoryComponent::ToggleInventoryWidget() const
{
	InventoryRequest.Broadcast();
}

const TArray<AEquipment*>& UInventoryComponent::GetInventory() const
{
	return Inventory;
}

void UInventoryComponent::SetInventoryIndex(AEquipment* Equipment, const uint8 Index)
{
	Inventory[Index] = Equipment;
	Inventory = Inventory; //forces rep notify to be called
	InventoryChanged.Broadcast();
}

void UInventoryComponent::DisplayInventory() const
{
	/*FString Result;
	for (EEquipmentID ID : Inventory)
	{
		Result += FString::FromInt((uint8)ID) + FString("-");
	}
	UKismetSystemLibrary::PrintString(GetWorld(), Result);*/
}

#pragma endregion

#pragma region Helper Functions

bool UInventoryComponent::DetermineFreeSpot(uint8& Index) const
{
	bool result = false;

	for (uint8 i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i] == nullptr)
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
		Inventory[i] = nullptr;
	}
	InventoryChanged.Broadcast();
}

#pragma endregion