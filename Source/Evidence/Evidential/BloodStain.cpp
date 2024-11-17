// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodStain.h"
#include "Components/BoxComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Items/Equipment/Swab.h"
#include "Evidence/Evidence.h"

ABloodStain::ABloodStain()
{
	bReplicates = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->bHiddenInGame = false;
	Box->SetVisibility(true);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	Box->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
	RootComponent = Box;

	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));

	bEnabled = true;

	PrimaryActorTick.bCanEverTick = true;
}

bool ABloodStain::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const
{
	const ABaseCharacter* const InteractingCharacter = Cast<ABaseCharacter>(InteractingActor);

	if (InteractingCharacter)
	{
		ASwab* const Swab = Cast<ASwab>(InteractingCharacter->GetEquipped());

		if (Swab && Swab->hasCapturesRemaining())
		{
			return true;
		}
	}

	return false;
}

void ABloodStain::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	const ABaseCharacter* const InteractingCharacter = Cast<ABaseCharacter>(InteractingActor);

	if (InteractingCharacter)
	{
		ASwab* const Swab = Cast<ASwab>(InteractingCharacter->GetEquipped());

		if (Swab)
		{
			Swab->ApplyToBloodStain(this);
		}
	}
}

FString ABloodStain::GetInteractionString_Implementation()
{
	return FString("Use swab");
}

void ABloodStain::BeginPlay()
{
	Super::BeginPlay();

	Stimulus->RegisterForSense(UAISense_Sight::StaticClass());
	Stimulus->RegisterWithPerceptionSystem();
}

EEvidentialType ABloodStain::GetType() const
{
	return EEvidentialType::Blood;
}

float ABloodStain::GetBaseWorth() const
{
	return 0.0f;
}

void ABloodStain::Disable()
{
	MulticastDisable();
}

void ABloodStain::MulticastDisable_Implementation()
{
	Box->bHiddenInGame = true;
	Box->SetVisibility(false);
	bEnabled = false;
}