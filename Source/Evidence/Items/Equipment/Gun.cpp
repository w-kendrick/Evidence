// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Net/UnrealNetwork.h"

AGun::AGun()
{
	EquipmentName = FString(TEXT("Gun"));
	MaxClipSize = 8;
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentClip(GetMaxClipSize());
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

void AGun::AddAmmoToClip(const uint8 Addition)
{
	SetCurrentClip(CurrentClip + Addition);
}

void AGun::SetCurrentClip(const uint8 NewClip)
{
	CurrentClip = FMath::Clamp(NewClip, 0, GetMaxClipSize());
	OnAmmoChanged.Broadcast(CurrentClip);
}

uint8 AGun::GetMaxClipSize() const
{
	return MaxClipSize;
}
