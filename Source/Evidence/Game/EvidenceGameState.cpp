// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AHub* AEvidenceGameState::GetHub()
{
	if (Hub)
	{
		return Hub;
	}

	Hub = Cast<AHub>(UGameplayStatics::GetActorOfClass(GetWorld(), AHub::StaticClass()));
	return Hub;
}

void AEvidenceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEvidenceGameState, Cash);
}

void AEvidenceGameState::AwardCash(const float Amount)
{
	Cash += Amount;
}

bool AEvidenceGameState::SpendCash(const float Amount)
{
	if (GetCash() < Amount)
	{
		return false;
	}

	Cash -= Amount;
	return true;
}

void AEvidenceGameState::OnRep_Cash(float PrevCash)
{
	OnCashChanged.Broadcast(Cash);
}
