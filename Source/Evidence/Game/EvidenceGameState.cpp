// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Game/EvidenceGameMode.h"

#pragma region Core

AEvidenceGameState::AEvidenceGameState()
{
	NetUpdateFrequency = 10;
}

void AEvidenceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEvidenceGameState, SetupCountdown);
	DOREPLIFETIME(AEvidenceGameState, Night);
	DOREPLIFETIME(AEvidenceGameState, Cash);
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

AHub* AEvidenceGameState::GetHub()
{
	if (Hub)
	{
		return Hub;
	}

	Hub = Cast<AHub>(UGameplayStatics::GetActorOfClass(GetWorld(), AHub::StaticClass()));
	return Hub;
}

#pragma region Night

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

void AEvidenceGameState::AwardCash(const float Amount)
{
	Cash += Amount;
	OnCashChanged.Broadcast(Cash);
}

bool AEvidenceGameState::SpendCash(const float Amount)
{
	if (GetCash() < Amount)
	{
		return false;
	}

	Cash -= Amount;
	OnCashChanged.Broadcast(Cash);
	return true;
}

void AEvidenceGameState::OnRep_Cash(float PrevCash)
{
	OnCashChanged.Broadcast(Cash);
}

#pragma endregion