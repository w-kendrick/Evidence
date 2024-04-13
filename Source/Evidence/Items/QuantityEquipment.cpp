// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantityEquipment.h"
#include "Net/UnrealNetwork.h"

AQuantityEquipment::AQuantityEquipment()
{
}

void AQuantityEquipment::BeginPlay()
{
	Super::BeginPlay();

	Quantity = MaxQuantity;
	OnQuantityChanged.Broadcast(Quantity);
}

void AQuantityEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuantityEquipment, Quantity);
}

void AQuantityEquipment::OnRep_Quantity(const uint8 OldQuantity)
{
	OnQuantityChanged.Broadcast(Quantity);
}

void AQuantityEquipment::Consume(const uint8 Amount, bool& isExhausted)
{
	isExhausted = false;
	Quantity -= Amount;
	OnQuantityChanged.Broadcast(Quantity);

	if (Quantity <= 0)
	{
		isExhausted = true;
	}
}