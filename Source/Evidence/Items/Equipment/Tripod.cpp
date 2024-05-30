// Fill out your copyright notice in the Description page of Project Settings.


#include "Tripod.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/EvidenceCharacter.h"

ATripod::ATripod()
{
	HoldLocation = CreateDefaultSubobject<USphereComponent>(TEXT("HoldLocation"));
	HoldLocation->SetupAttachment(RootComponent);
	HoldLocation->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

void ATripod::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATripod, EmplacedEquipment);
	DOREPLIFETIME(ATripod, isPlaced);
}

void ATripod::Plant()
{
	isPlaced = true;
}

void ATripod::Pickup(AEvidenceCharacter* Char)
{
	Super::Pickup(Char);
	isPlaced = false;
}

bool ATripod::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	if (InteractionComponent == WorldMesh)
	{
		return Super::IsAvailableForInteraction_Implementation(InteractionComponent);
	}
	else
	{
		return isPlaced;
	}
}

void ATripod::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	if (InteractionComponent == WorldMesh)
	{
		Super::PostInteract_Implementation(InteractingActor, InteractionComponent);
	}
	else
	{
		AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(InteractingActor);
		if (Char)
		{
			if (EmplacedEquipment)
			{
				Unemplace(EmplacedEquipment);

				Char->Pickup(EmplacedEquipment);

				EmplacedEquipment = nullptr;
			}
			else
			{
				AEquipment* const Equipped = Char->GetEquipped();
				if (Equipped)
				{
					Char->Drop();

					EmplacedEquipment = Equipped;

					Emplace(Equipped);
				}
			}
		}
	}
}

void ATripod::Emplace(AEquipment* Equipment)
{
	const FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	Equipment->AttachToComponent(HoldLocation, Rule);
}

void ATripod::Unemplace(AEquipment* Equipment)
{
	const FDetachmentTransformRules Rule = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
	Equipment->GetWorldMesh()->DetachFromComponent(Rule);
}

void ATripod::OnRep_EmplacedEquipment(AEquipment* PrevEquipment)
{
	if (EmplacedEquipment)
	{
		Emplace(EmplacedEquipment);
	}

	if (PrevEquipment)
	{
		Unemplace(PrevEquipment);
	}
}