// Fill out your copyright notice in the Description page of Project Settings.


#include "Locker.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Evidence.h"

ALocker::ALocker()
	: Storage(STORAGE_CAPACITY)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terminal"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

void ALocker::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALocker, Storage);
}

bool ALocker::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return true;
}

void ALocker::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
}

FString ALocker::GetInteractionString_Implementation()
{
	return FString("Locker");
}

void ALocker::SetLockerStorage(AEquipment* const Equipment, const uint8 Index)
{
	Storage.AddEntry(Equipment, Index);
}

void ALocker::OnRep_Storage()
{
}
