// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBench.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Evidence/EvidencePlayerController.h"

AAttachmentBench::AAttachmentBench()
{
	PrimaryActorTick.bCanEverTick = false;

	Bench = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bench"));
	Bench->SetupAttachment(RootComponent);
	Bench->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

bool AAttachmentBench::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return true;
}

void AAttachmentBench::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	if (HasAuthority())
	{
		AEvidencePlayerCharacter* const Char = Cast<AEvidencePlayerCharacter>(InteractingActor);
		if (Char)
		{
			AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Char->GetController());
			if (EPC)
			{
				EPC->ClientSetAttachmentWidgetVisibility(true);
			}
		}
	}
}
