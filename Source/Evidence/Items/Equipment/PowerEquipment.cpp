// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerEquipment.h"
#include "Net/UnrealNetwork.h"

APowerEquipment::APowerEquipment()
{
	isPowerActive = false;
	MaxPower = 100;
	ActiveDrainRate = 1;
}

void APowerEquipment::BeginPlay()
{
	Super::BeginPlay();

	SetPower(MaxPower);
	SetPowerActive(false);
}

void APowerEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APowerEquipment, Power);
}

void APowerEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPowerActive)
	{
		const float NewPower = FMath::Clamp(Power - DeltaTime * ActiveDrainRate, 0, MaxPower);
		SetPower(NewPower);

		if (Power == 0)
		{
			SetPowerActive(false);
		}
	}
}

void APowerEquipment::SetPower(const float NewPower)
{
	Power = NewPower;
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void APowerEquipment::SetPowerActive(const bool NewActive, const bool bMulticast)
{
	isPowerActive = NewActive;
	if (bMulticast)
	{
		MulticastSetPowerActive(NewActive);
	}
	OnActiveChanged.Broadcast(isPowerActive);

	if (isPowerActive)
	{
		ActivatePower();
	}
	else
	{
		DeactivatePower();
	}
}

void APowerEquipment::MulticastSetPowerActive_Implementation(const bool NewActive)
{
	SetPowerActive(NewActive);
}

void APowerEquipment::ToggleActivation()
{
	if (Power > 0)
	{
		SetPowerActive(!isPowerActive, true);
	}
}

void APowerEquipment::OnRep_Power(const float PrevPower)
{
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void APowerEquipment::ActivatePower()
{
	
}

void APowerEquipment::DeactivatePower()
{
	
}