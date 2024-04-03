// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Net/UnrealNetwork.h"

AGun::AGun()
{
	MaxClipSize = 8;
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	CurrentClip = MaxClipSize;
	OnAmmoChanged.Broadcast(CurrentClip);
}

void AGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGun, CurrentClip);
}

void AGun::OnRep_CurrentClip(const uint8 OldClip)
{
	OnAmmoChanged.Broadcast(CurrentClip);
}

void AGun::SetCurrentClip(const uint8 NewClip)
{
	CurrentClip = FMath::Clamp(NewClip, 0, MaxClipSize);
	OnAmmoChanged.Broadcast(CurrentClip);
}