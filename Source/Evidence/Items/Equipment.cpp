// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "Components/SkeletalMeshComponent.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Evidence/Character/Abilities/EIGameplayAbility.h"
#include "Equipment/Components/AttachmentComponent.h"
#include "Equipment/EquipmentAttachment.h"

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

void AEquipment::AddAttachment(AEquipmentAttachment* const Attachment)
{
	const TSubclassOf<UAttachmentComponent>& ComponentClass = Attachment->GetComponentClass();
	UAttachmentComponent* const Comp = NewObject<UAttachmentComponent>(this, ComponentClass);
	Comp->RegisterComponent();

	Comp->AttachTo(this);
}

void AEquipment::AddAttachmentAbility(const TSubclassOf<UEIGameplayAbility>& Ability)
{
	Abilities.Add(Ability);

	AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetOwner());
	if (Char)
	{
		if (Char->GetEquipped() == this)
		{
			UCharacterAbilitySystemComponent* const ASC = Char->GetCharacterAbilitySystemComponent();

			if (GetLocalRole() != ROLE_Authority || !ASC)
			{
				return;
			}

			GrantedAbilities.Add(ASC->GiveAbility(FGameplayAbilitySpec(Ability, 0, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this)));
		}
	}
}

bool AEquipment::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return !bIsPickedUp;
}

void AEquipment::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(InteractingActor);
	if (Char)
	{
		Char->Pickup(this);
	}
}

void AEquipment::Pickup(AEvidenceCharacter* Char)
{
	Attach(Char, true);

	AddAbilities(Char);
}

void AEquipment::Drop()
{
	if (AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetOwner()))
	{
		RemoveAbilities(Char);
	}

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

void AEquipment::Attach(AEvidenceCharacter* Char, const bool isVisible)
{
	SetOwner(Char);
	bIsPickedUp = true;

	USkeletalMeshComponent* const CharWorldMesh = Char->GetMesh();
	const FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	WorldMesh->AttachToComponent(CharWorldMesh, Rule, EquipSocket);
	WorldMesh->SetVisibility(isVisible);

	AEvidencePlayerCharacter* PlayerChar = Cast<AEvidencePlayerCharacter>(Char);
	if (PlayerChar)
	{
		USkeletalMeshComponent* const CharLocalMesh = PlayerChar->GetMesh1P();
		LocalMesh->AttachToComponent(CharLocalMesh, Rule, EquipSocket);
		LocalMesh->SetVisibility(isVisible);
	}
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

void AEquipment::AddAbilities(AEvidenceCharacter* Char)
{
	UCharacterAbilitySystemComponent* const ASC = Char->GetCharacterAbilitySystemComponent();

	if (GetLocalRole() != ROLE_Authority || !ASC)
	{
		return;
	}

	for (const TSubclassOf<UEIGameplayAbility>& Ability : Abilities)
	{
		GrantedAbilities.Add(ASC->GiveAbility(FGameplayAbilitySpec(Ability, 0, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this)));
	}
}

void AEquipment::RemoveAbilities(AEvidenceCharacter* Char)
{
	UCharacterAbilitySystemComponent* const ASC = Char->GetCharacterAbilitySystemComponent();

	if (GetLocalRole() != ROLE_Authority || !ASC)
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : GrantedAbilities)
	{
		ASC->ClearAbility(Handle);
	}

	GrantedAbilities.Empty();
}
