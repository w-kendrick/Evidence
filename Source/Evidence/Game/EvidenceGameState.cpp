// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameState.h"
#include "Evidence/Hub/Hub.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Evidence.h"

#pragma region Core

AEvidenceGameState::AEvidenceGameState()
{
	NetUpdateFrequency = 10;

	Night = DEFAULT_STARTING_NIGHT;
	Cash = DEFAULT_STARTING_CASH;
}

void AEvidenceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEvidenceGameState, SetupCountdown);
	DOREPLIFETIME(AEvidenceGameState, Night);
	DOREPLIFETIME(AEvidenceGameState, Cash);
	DOREPLIFETIME(AEvidenceGameState, CandidateSpectatees);
}

void AEvidenceGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::Setup)
	{
		SetupCountdown -= DeltaTime;
	}
}

#pragma endregion

#pragma region Match State

void AEvidenceGameState::SetMatchState(const FName& State)
{
	MatchState = State;
}

void AEvidenceGameState::OnRep_MatchState()
{
	Super::OnRep_MatchState();

	OnMatchStateChanged.Broadcast(MatchState);
}

void AEvidenceGameState::SetSetupCountdownLength(const float InCountdownLength)
{
	SetupCountdown = InCountdownLength;
}

#pragma endregion

#pragma region Night

void AEvidenceGameState::EndNight()
{
	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	Hub->ConsumeCaptures();
}

void AEvidenceGameState::SetNight(const uint32 NewNight)
{
	Night = NewNight;
	OnNightChanged.Broadcast(Night);
}

void AEvidenceGameState::OnRep_Night(uint32 PrevNight)
{
	OnNightChanged.Broadcast(Night);
}

#pragma endregion

#pragma region Cash

void AEvidenceGameState::SetCash(const float NewCash)
{
	Cash = NewCash;
	OnCashChanged.Broadcast(Cash);
}

void AEvidenceGameState::AwardCash(const float Amount)
{
	SetCash(Cash + Amount);
}

bool AEvidenceGameState::SpendCash(const float Amount)
{
	if (GetCash() < Amount)
	{
		return false;
	}

	SetCash(Cash - Amount);
	return true;
}

void AEvidenceGameState::OnRep_Cash(float PrevCash)
{
	OnCashChanged.Broadcast(Cash);
}

#pragma endregion

#pragma region Spectatees

void AEvidenceGameState::AddLivingPlayer(APlayerController* const PlayerController)
{
	CandidateSpectatees.AddEntry(PlayerController->GetPawn());
	OnCandidateSpectateesChanged.Broadcast(CandidateSpectatees);
}

void AEvidenceGameState::RemoveLivingPlayer(APlayerController* const PlayerController)
{
	CandidateSpectatees.RemoveEntry(PlayerController->GetPawn());
	OnCandidateSpectateesChanged.Broadcast(CandidateSpectatees);
}

void AEvidenceGameState::OnRep_CandidateSpectatees()
{
	OnCandidateSpectateesChanged.Broadcast(CandidateSpectatees);
}

#pragma endregion