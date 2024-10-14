// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalButton.h"
#include "Evidence/Evidence.h"

APhysicalButton::APhysicalButton()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(COLLISION_ABILITY, ECollisionResponse::ECR_Overlap);

	bIsAvailable = false;
}

bool APhysicalButton::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return bIsAvailable;
}

void APhysicalButton::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	Interact();
}

FString APhysicalButton::GetInteractionString_Implementation()
{
	return DisplayString;
}

void APhysicalButton::SetIsAvailable(const bool bNewValue)
{
	bIsAvailable = bNewValue;
}
