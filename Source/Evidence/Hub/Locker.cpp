// Fill out your copyright notice in the Description page of Project Settings.


#include "Locker.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Evidence.h"
#include "Evidence/Player/EvidencePlayerController.h"

ALocker::ALocker()
	: Storage(STORAGE_CAPACITY)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terminal"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();

	OnLockerStorageChanged.Broadcast(Storage);
}

void ALocker::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALocker, Storage);
}

FString ALocker::GetInteractionString_Implementation()
{
	return FString("Locker");
}

void ALocker::SetEquipmentAtIndex(AEquipment* const Equipment, const uint8 Index)
{
	Storage.AddEntry(Equipment, Index);
	OnLockerStorageChanged.Broadcast(Storage);
}

AEquipment* ALocker::GetEquipmentAtIndex(const uint8 Index) const
{
	return Storage[Index].GetEquipment();
}

void ALocker::OnInteract()
{
	AEvidencePlayerController* const EvidencePlayerController = Cast<AEvidencePlayerController>(Interactor->GetController());
	if (EvidencePlayerController)
	{
		SetOwner(Interactor);
		EvidencePlayerController->ClientSetLockerWidgetVisibility(true);
	}
}

void ALocker::OnRep_Storage()
{
	OnLockerStorageChanged.Broadcast(Storage);
}
