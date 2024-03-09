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
	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(InteractingActor);
	if (Char)
	{
		Char->Pickup(this);
	}
}

void AEquipment::Pickup(AEvidenceCharacter* Char)
{
	SetOwner(Char);
	bIsPickedUp = true;

	USkeletalMeshComponent* CharWorldMesh = Char->GetMesh();
	const FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	WorldMesh->AttachToComponent(CharWorldMesh, Rule, EquipSocket);

	AEvidencePlayerCharacter* PlayerChar = Cast<AEvidencePlayerCharacter>(Char);
	if (PlayerChar)
	{
		USkeletalMeshComponent* CharLocalMesh = PlayerChar->GetMesh1P();
		LocalMesh->AttachToComponent(CharLocalMesh, Rule, EquipSocket);
	}
}

void AEquipment::Drop()
{
	SetOwner(nullptr);
	bIsPickedUp = false;

	const FDetachmentTransformRules Rule = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
	WorldMesh->DetachFromComponent(Rule);
	LocalMesh->DetachFromComponent(Rule);

	FVector Location;
	FRotator Rotation;
	FindGround(Location, Rotation);

	SetActorLocation(Location);
	SetActorRotation(Rotation);
}

void AEquipment::FindGround(FVector& Location, FRotator& Rotation) const
{
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = End + FVector::UpVector * -1 * MaxGroundDistance;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		Location = Hit.Location;
		Rotation = Hit.Normal.Rotation();
		return;
	}
	Location = Start;
	Rotation = GetActorRotation();
}