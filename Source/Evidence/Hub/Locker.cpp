// Fill out your copyright notice in the Description page of Project Settings.


#include "Locker.h"
#include "Net/UnrealNetwork.h"

ALocker::ALocker()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ALocker::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALocker, Storage);
}

void ALocker::SetLockerStorage(AEquipment* const Equipment, const uint8 Index)
{
	
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALocker::OnRep_Storage()
{
}
