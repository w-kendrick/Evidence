// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Interfaces/PowerInterface.h"

UPowerComponent::UPowerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	isPowerActive = false;
	MaxPower = 100;
	ActiveDrainRate = 1;
}


void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();

	SetPower(MaxPower);
	SetPowerActive(false);
}

void UPowerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPowerComponent, Power);
	DOREPLIFETIME(UPowerComponent, isPowerActive);
}

void UPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UPowerComponent::SetPower(const float NewPower)
{
	Power = NewPower;
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void UPowerComponent::SetPowerActive(const bool NewActive)
{
	isPowerActive = NewActive;
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

void UPowerComponent::ToggleActivation()
{
	if (Power > 0)
	{
		SetPowerActive(!isPowerActive);
	}
}

void UPowerComponent::OnRep_Power(const float PrevPower)
{
	OnPowerChanged.Broadcast(Power, MaxPower);
}

void UPowerComponent::OnRep_IsPowerActive(const bool PrevIsActive)
{
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

void UPowerComponent::ActivatePower()
{
	IPowerInterface* const PowerInterface = Cast<IPowerInterface>(GetOwner());
	if (PowerInterface)
	{
		PowerInterface->Activate();
	}
}

void UPowerComponent::DeactivatePower()
{
	IPowerInterface* const PowerInterface = Cast<IPowerInterface>(GetOwner());
	if (PowerInterface)
	{
		PowerInterface->Deactivate();
	}
}

