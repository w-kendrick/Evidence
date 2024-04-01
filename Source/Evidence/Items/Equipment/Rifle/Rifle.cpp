// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Net/UnrealNetwork.h"

ARifle::ARifle()
{
	MaxClipSize = 8;
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();

	CurrentClip = MaxClipSize;
	OnAmmoChanged.Broadcast(CurrentClip);
}

void ARifle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARifle, CurrentClip);
}

void ARifle::OnRep_CurrentClip(const uint8 OldClip)
{
	OnAmmoChanged.Broadcast(CurrentClip);
}

void ARifle::SetCurrentClip(const uint8 NewClip)
{
	CurrentClip = FMath::Clamp(NewClip, 0, MaxClipSize);
	OnAmmoChanged.Broadcast(CurrentClip);
}