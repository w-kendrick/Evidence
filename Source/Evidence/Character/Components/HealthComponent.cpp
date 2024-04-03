// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	MaxHealth = 100.f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, isAlive);
}

void UHealthComponent::ReceiveDamage(const float Amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Received damage");

	if (Amount > 0 && isAlive)
	{
		Health = FMath::Clamp(Health - Amount, 0, MaxHealth);
		OnHealthChanged.Broadcast(Health);

		if (Health == 0)
		{
			isAlive = false;
			OnDeath.Broadcast();
		}
	}
}

void UHealthComponent::OnRep_IsAlive(const bool PrevIsAlive)
{
	if (!isAlive && PrevIsAlive)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::OnRep_Health(const float PrevHealth)
{
	OnHealthChanged.Broadcast(PrevHealth);
}
