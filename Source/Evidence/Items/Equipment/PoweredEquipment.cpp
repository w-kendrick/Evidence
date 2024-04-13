// Fill out your copyright notice in the Description page of Project Settings.


#include "PoweredEquipment.h"
#include "Net/UnrealNetwork.h"

APoweredEquipment::APoweredEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
	isActive = false;
	MaxPower = 100;
	ActiveDrainRate = 1;
}

void APoweredEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APoweredEquipment, Power);
	DOREPLIFETIME(APoweredEquipment, isActive);
}

void APoweredEquipment::BeginPlay()
{
	Super::BeginPlay();

	SetPower(MaxPower);
	SetActive(false);
}

void APoweredEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isActive)
	{
		const float NewPower = FMath::Clamp(Power - DeltaTime * ActiveDrainRate, 0, MaxPower);
		SetPower(NewPower);

		if (Power == 0)
		{
			SetActive(false);
		}
	}
}

void APoweredEquipment::SetPower(const float NewPower)
{
	Power = NewPower;
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void APoweredEquipment::SetActive(const bool NewActive)
{
	isActive = NewActive;
	OnActiveChanged.Broadcast(isActive);

	if (isActive)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void APoweredEquipment::ToggleActivation()
{
	if (Power > 0)
	{
		SetActive(!isActive);
	}
}

void APoweredEquipment::OnRep_Power(const float PrevPower)
{
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void APoweredEquipment::OnRep_IsActive(const bool PrevIsActive)
{
	OnActiveChanged.Broadcast(isActive);

	if (isActive)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}
