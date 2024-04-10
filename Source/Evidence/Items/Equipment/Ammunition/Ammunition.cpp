// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammunition.h"
#include "Net/UnrealNetwork.h"

AAmmunition::AAmmunition()
{
	EquipmentName = FString("Ammo");
}

void AAmmunition::Consume(const uint8 Amount)
{
	Quantity -= Amount;

	if (Quantity <= 0)
	{
		Destroy();
	}
}

void AAmmunition::BeginPlay()
{
	Super::BeginPlay();

	Quantity = MaxQuantity;
}

void AAmmunition::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAmmunition, Quantity);
}

void AAmmunition::OnRep_Quantity(const uint8 OldQuantity)
{
	OnQuantityChanged.Broadcast(Quantity);
}
