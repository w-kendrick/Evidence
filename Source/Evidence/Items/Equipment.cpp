// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Components/SkeletalMeshComponent.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AEquipment::AEquipment()
{
	bReplicates = true;

	WorldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WorldMesh"));
	RootComponent = WorldMesh;
	WorldMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WorldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WorldMesh->SetCollisionResponseToChannel(COLLISION_ABILITY, ECollisionResponse::ECR_Overlap);
	WorldMesh->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
	WorldMesh->SetGenerateOverlapEvents(true);
	WorldMesh->bOwnerNoSee = true;
	WorldMesh->bOnlyOwnerSee = false;

	LocalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LocalMesh"));
	LocalMesh->SetupAttachment(RootComponent);
	LocalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LocalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocalMesh->SetGenerateOverlapEvents(false);
	LocalMesh->bOwnerNoSee = false;
	LocalMesh->bOnlyOwnerSee = true;
}

bool AEquipment::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return !bIsPickedUp;
}

void AEquipment::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	AEvidencePlayerCharacter* Char = Cast<AEvidencePlayerCharacter>(InteractingActor);
	if (Char)
	{
		Pickup(Char);
	}
}

void AEquipment::HandlePickup(AEvidencePlayerCharacter* Char)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Pickup");
	
	if (UKismetSystemLibrary::IsServer(GetWorld()))
	{
		MulticastPickup(Char);
	}
	else
	{
		Pickup(Char);
	}
}

void AEquipment::MulticastPickup_Implementation(AEvidencePlayerCharacter* Char)
{
	if (Char->IsLocallyControlled())
	{
		if (!bIsPickedUp)
		{
			Pickup(Char);
		}
	}
	else
	{
		Pickup(Char);
	}
}

void AEquipment::Pickup(AEvidencePlayerCharacter* Char)
{
	SetOwner(Char);
	bIsPickedUp = true;

	USkeletalMeshComponent* CharWorldMesh = Char->GetMesh();
	USkeletalMeshComponent* CharLocalMesh = Char->GetMesh1P();
	FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	WorldMesh->AttachToComponent(CharWorldMesh, Rule, EquipSocket);
	LocalMesh->AttachToComponent(CharLocalMesh, Rule, EquipSocket);
}
