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
	MatchState = State;

	if (MatchState == MatchState::PreSetup || MatchState == MatchState::InProgress)
	{
		SetIsAvailable(true);
		SetInteractString(FString("Begin"));
		SetInteractDuration(0.0f);
	}
	else if (MatchState == MatchState::Setup)
	{
		SetIsAvailable(true);
		SetInteractString(FString("End Setup Period"));
		SetInteractDuration(1.0f);
	}
	else if (MatchState == MatchState::Night)
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
	if (MatchState == MatchState::PreSetup || MatchState == MatchState::InProgress)
	{
		ServerEndPreSetup();
	}
	else if (MatchState == MatchState::Setup)
	{
		ServerEndSetup();
	}
	else if (MatchState == MatchState::Night)
	{
		ServerEndNight();
	}
}

void AMatchStateButton::ServerEndPreSetup_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
}

void AMatchStateButton::ServerEndSetup_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Start Night");
		EvidenceGameMode->StartNight();
	}
}

void AMatchStateButton::ServerEndNight_Implementation()
{
	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "End Night");
		EvidenceGameMode->EndNight();
	}
}