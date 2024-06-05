// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBench.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Items/Equipment/Components/AttachmentComponent.h"

AAttachmentBench::AAttachmentBench()
{
	PrimaryActorTick.bCanEverTick = false;

	Bench = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terminal"));
	Bench->SetupAttachment(RootComponent);
	Bench->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

bool AAttachmentBench::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return true;
}

void AAttachmentBench::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	const AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(InteractingActor);

	if (Char)
	{
		const AEquipment* const Equipment = Char->GetEquipped();

		if (Equipment)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Valid equipment");
			const TMap<EAttachmentType, UAttachmentComponent*>& Attachments = Equipment->GetAttachments();

			for (const TPair<EAttachmentType, UAttachmentComponent*>& Elem : Attachments)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, UEnum::GetValueAsString(Elem.Key));
			}
		}
	}
}
