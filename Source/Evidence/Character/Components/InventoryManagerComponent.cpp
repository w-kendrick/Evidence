// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryManagerComponent::UInventoryManagerComponent()
	: EquipmentList(GetOwner())
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryManagerComponent::Pickup(AEquipment* Equipment, const uint8 Index)
{
	EquipmentList.AddEntry(Equipment, Index);
}

void UInventoryManagerComponent::Drop(const uint8 Index)
{
	EquipmentList.RemoveEntry(Index);
}

AEquipment* UInventoryManagerComponent::GetEquipped() const
{
	return EquipmentList[EquippedIndex].GetEquipment();
}

void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryManagerComponent, EquipmentList);
	DOREPLIFETIME(UInventoryManagerComponent, EquippedIndex);
}

void UInventoryManagerComponent::OnRep_EquipmentList(const FEquipmentList PrevList)
{
}

void UInventoryManagerComponent::OnRep_EquippedIndex(const uint8 PrevIndex)
{
}
