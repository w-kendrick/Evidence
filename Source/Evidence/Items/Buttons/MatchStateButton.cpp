// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchStateButton.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"

AMatchStateButton::AMatchStateButton()
{
	SetInteractString(FString("Begin"));
	SetInteractDuration(0.0f);
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
	if (State == MatchState::PreSetup || State == MatchState::InProgress)
	{
		SetIsAvailable(true);
		SetInteractString(FString("Begin"));
		SetInteractDuration(0.0f);
	}
	else if (State == MatchState::Setup)
	{
		SetIsAvailable(true);
		SetInteractString(FString("End Setup Period"));
		SetInteractDuration(1.0f);
	}
	else if (State == MatchState::Night)
	{
		SetIsAvailable(true);
		SetInteractString(FString("End Night"));
		SetInteractDuration(2.5f);
	}
	else
	{
		SetIsAvailable(false);
	}
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
