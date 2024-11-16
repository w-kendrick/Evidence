// Fill out your copyright notice in the Description page of Project Settings.

#include "SingleUserInteractable.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Player/EvidencePlayerController.h"

ASingleUserInteractable::ASingleUserInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ASingleUserInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASingleUserInteractable, Interactor);
}

bool ASingleUserInteractable::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const
{
	return !Interactor;
}

void ASingleUserInteractable::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	if (HasAuthority())
	{
		ABaseCharacter* const Char = Cast<ABaseCharacter>(InteractingActor);
		if (Char)
		{
			Interactor = Char;

			AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Interactor->GetController());
			if (EPC)
			{
				SetOwner(InteractingActor);
				OnInteract();
			}
		}
	}
}

void ASingleUserInteractable::Relinquish()
{
	ServerRelinquish();
}

void ASingleUserInteractable::ServerRelinquish_Implementation()
{
	Interactor = nullptr;
	SetOwner(nullptr);
}

void ASingleUserInteractable::OnInteract()
{
}
