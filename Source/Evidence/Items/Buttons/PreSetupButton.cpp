// Fill out your copyright notice in the Description page of Project Settings.


#include "PreSetupButton.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"

APreSetupButton::APreSetupButton()
{
	DisplayString = FString("Begin");
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
	SetIsAvailable((State == MatchState::PreSetup) || (State == MatchState::InProgress));
}

void APreSetupButton::Interact()
{
	ServerEndPreSetup();
}

void APreSetupButton::ServerEndPreSetup_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
}
