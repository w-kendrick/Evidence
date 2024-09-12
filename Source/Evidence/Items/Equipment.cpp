// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Components/SkeletalMeshComponent.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Equipment/EquipmentAttachment.h"
#include "AdvancedAbilityComponent.h"

AEquipment::AEquipment()
{
	bReplicates = true;

	WorldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WorldMesh"));
	RootComponent = WorldMesh;
	WorldMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WorldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WorldMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	WorldMesh->SetCollisionResponseToChannel(COLLISION_ABILITY, ECollisionResponse::ECR_Overlap);
	WorldMesh->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
	WorldMesh->SetGenerateOverlapEvents(true);
	WorldMesh->bOwnerNoSee = true;
	WorldMesh->bOnlyOwnerSee = false;
	WorldMesh->SetIsReplicated(true);

	LocalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LocalMesh"));
	LocalMesh->SetupAttachment(RootComponent);
	LocalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LocalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocalMesh->SetGenerateOverlapEvents(false);
	LocalMesh->bOwnerNoSee = false;
	LocalMesh->bOnlyOwnerSee = true;
	LocalMesh->SetIsReplicated(true);

	EquipmentName = FString(TEXT("Equipment"));
}

void AEquipment::AddAttachment(AEquipmentAttachment* const Attachment, const EAttachmentType Type)
{
	Attachments[Type] = Attachment;
	OnAttachmentsUpdated.Broadcast();

	if (Attachment)
	{
		Attachment->AttachTo(this);
	}
}

void AEquipment::RemoveAttachment(const EAttachmentType Type)
{
	AEquipmentAttachment* const Attachment = Attachments[Type];

	if (Attachment)
	{
		Attachment->DetachFrom();
	}

	Attachments[Type] = nullptr;
	OnAttachmentsUpdated.Broadcast();
}

bool AEquipment::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return !bIsPickedUp;
}

void AEquipment::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	ABaseCharacter* const Char = Cast<ABaseCharacter>(InteractingActor);
	if (Char)
	{
		Char->Pickup(this);
	}
}

FString AEquipment::GetInteractionString_Implementation()
{
	return FString("Pickup ") + GetEquipmentName();
}

void AEquipment::Pickup(ABaseCharacter* Char)
{
	Attach(Char, true);

	AddAbilities(Char);
}

void AEquipment::Stow(ABaseCharacter* Char)
{
	Attach(Char, false);

	RemoveAbilities(Char);
}

void AEquipment::Drop()
{
	if (ABaseCharacter* const Char = Cast<ABaseCharacter>(GetOwner()))
	{
		RemoveAbilities(Char);
	}

	Detach();
}

void AEquipment::Attach(ABaseCharacter* Char, const bool isVisible)
{
	SetOwner(Char);
	bIsPickedUp = true;

	USkeletalMeshComponent* const CharWorldMesh = Char->GetMesh();
	const FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	WorldMesh->AttachToComponent(CharWorldMesh, Rule, EquipSocket);
	WorldMesh->SetVisibility(isVisible);

	ABaseCharacter* PlayerChar = Cast<ABaseCharacter>(Char);
	if (PlayerChar)
	{
		USkeletalMeshComponent* const CharLocalMesh = PlayerChar->GetMesh1P();
		LocalMesh->AttachToComponent(CharLocalMesh, Rule, EquipSocket);
		LocalMesh->SetVisibility(isVisible);
	}
}

void AEquipment::Detach()
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
	const FVector Start = GetActorLocation();
	const FVector End = End + FVector::UpVector * -1 * MaxGroundDistance;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		Location = Hit.Location;
		Rotation = Hit.Normal.Rotation();
		return;
	}
	Location = Start;
	Rotation = GetActorRotation();
}

void AEquipment::AddAbilities(ABaseCharacter* Char)
{
	UAdvancedAbilityComponent* const ASC = Cast<UAdvancedAbilityComponent>(Char->GetAbilitySystemComponent());

	if (GetLocalRole() != ROLE_Authority || !ASC)
	{
		return;
	}
	
	AbilitySet->GiveToAbilitySystem(ASC, &GrantedHandles, this);
}

void AEquipment::RemoveAbilities(ABaseCharacter* Char)
{
	UAdvancedAbilityComponent* const ASC = Cast<UAdvancedAbilityComponent>(Char->GetAbilitySystemComponent());

	if (GetLocalRole() != ROLE_Authority || !ASC)
	{
		return;
	}
	
	GrantedHandles.TakeFromAbilitySystem(ASC);
}

AEquipmentAttachment* AEquipment::GetAttachment(const EAttachmentType Type) const
{
	return Attachments[Type];
}