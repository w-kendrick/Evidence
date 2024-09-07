// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBench.h"
#include "Evidence/Evidence.h"
#include "Evidence/Character/BaseCharacter.h"
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
		ABaseCharacter* const Char = Cast<ABaseCharacter>(InteractingActor);
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

FString AAttachmentBench::GetInteractionString_Implementation()
{
	return FString("Use attachments bench");
}
