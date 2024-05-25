// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceCaptureEquipment.h"
#include "Net/UnrealNetwork.h"

AEvidenceCaptureEquipment::AEvidenceCaptureEquipment()
{
	MaxCaptures = 1U;
}

void AEvidenceCaptureEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEvidenceCaptureEquipment, Captures);
}

void AEvidenceCaptureEquipment::OnRep_Captures(const TArray<FEvidentialCapture> PrevCaptures)
{
	OnRemainingCapturesChanged.Broadcast(MaxCaptures - Captures.Num());
}

TArray<FEvidentialCapture> AEvidenceCaptureEquipment::GetCaptures() const
{
	return Captures;
}

bool AEvidenceCaptureEquipment::hasCapturesRemaining() const
{
	return Captures.Num() < MaxCaptures;
}
