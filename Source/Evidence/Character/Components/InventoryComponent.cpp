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
}

void UInventoryComponent::OnRep_Inventory(TArray<EEquipmentID> NewInventory)
{
	DisplayInventory();
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
	const EEquipmentID ItemToEquip = Inventory[Index];

	PickupToInventory(Equipped, Index);

	const TSubclassOf<AEquipment> ClassToEquip = EGS->GetEquipmentClass(ItemToEquip);

	if (ClassToEquip)
	{
		AEquipment* Equipment = GetWorld()->SpawnActor<AEquipment>(ClassToEquip);

		PickupEquipped(Equipment);
	}
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

void UInventoryComponent::PickupToInventory(AEquipment* Equipment, const uint8 Index)
{
	if (Equipment)
	{
		const EEquipmentID EquipmentID = EGS->GetEquipmentID(Equipment->GetClass());

		Equipment->Destroy();

		SetInventoryIndex(EquipmentID, Index);
		DisplayInventory();
	}
}

void UInventoryComponent::TryDropFromInventory_Implementation(const uint8 Index)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Try drop from inventory");
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

void UInventoryComponent::DisplayInventory() const
{
	FString Result;
	for (EEquipmentID ID : Inventory)
	{
		Result += FString::FromInt((uint8)ID) + FString("-");
	}
	UKismetSystemLibrary::PrintString(GetWorld(), Result);
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