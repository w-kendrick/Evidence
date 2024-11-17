// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceCaptureEquipment.h"
#include "Net/UnrealNetwork.h"

AEvidenceCaptureEquipment::AEvidenceCaptureEquipment()
{
	MaxCaptures = 1U;
	RemainingCaptures = MaxCaptures;
}

void AEvidenceCaptureEquipment::BeginPlay()
{
	Super::BeginPlay();

	OnRemainingCapturesChanged.Broadcast(RemainingCaptures);
}

void AEvidenceCaptureEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEvidenceCaptureEquipment, RemainingCaptures);
}

void AEvidenceCaptureEquipment::OnRep_RemainingCaptures(const uint8 PrevRemaining)
{
	OnRemainingCapturesChanged.Broadcast(RemainingCaptures);
}

void AEvidenceCaptureEquipment::AddCapture(const FEvidentialCapture& Capture)
{
	Captures.Add(Capture);
	RemainingCaptures--;
	OnRemainingCapturesChanged.Broadcast(RemainingCaptures);
}

void AEvidenceCaptureEquipment::Clear()
{
	Captures.Empty();
	RemainingCaptures = MaxCaptures;
	OnRemainingCapturesChanged.Broadcast(RemainingCaptures);
}

TArray<FEvidentialCapture> AEvidenceCaptureEquipment::GetCaptures() const
{
	return Captures;
}

bool AEvidenceCaptureEquipment::hasCapturesRemaining() const
{
	return RemainingCaptures > 0;
}
