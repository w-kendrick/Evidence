// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchStateButton.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"

AMatchStateButton::AMatchStateButton()
{
	DisplayString = FString("Begin");
}

void AMatchStateButton::BeginPlay()
{
	Super::BeginPlay();

	AEvidenceGameState* const EvidenceGameState = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EvidenceGameState)
	{
		EvidenceGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnMatchStateChanged);
	}
}

void AMatchStateButton::OnMatchStateChanged(FName State)
{
	SetIsAvailable((State == MatchState::PreSetup) || (State == MatchState::InProgress));
}

void AMatchStateButton::Interact()
{
	ServerEndPreSetup();
}

void AMatchStateButton::ServerEndPreSetup_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
}
