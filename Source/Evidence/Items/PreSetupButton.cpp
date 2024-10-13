// Fill out your copyright notice in the Description page of Project Settings.


#include "PreSetupButton.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Evidence.h"

APreSetupButton::APreSetupButton()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(COLLISION_ABILITY, ECollisionResponse::ECR_Overlap);

	bIsAvailable = true;
}

void APreSetupButton::BeginPlay()
{
	Super::BeginPlay();

	AEvidenceGameState* const EvidenceGameState = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EvidenceGameState)
	{
		EvidenceGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnMatchStateChanged);
	}
}

void APreSetupButton::OnMatchStateChanged(FName State)
{
	bIsAvailable = (State == MatchState::PreSetup) || (State == MatchState::InProgress);
}

void APreSetupButton::ServerEndPreSetup_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
}

bool APreSetupButton::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return bIsAvailable;
}

void APreSetupButton::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	ServerEndPreSetup();
}

FString APreSetupButton::GetInteractionString_Implementation()
{
	return FString("Begin");
}
