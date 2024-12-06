// Fill out your copyright notice in the Description page of Project Settings.


#include "Swab.h"
#include "Evidence/Evidential/BloodStain.h"

ASwab::ASwab()
{
	MaxCaptures = 1;

	EquipmentAbbreviation = FString(TEXT("SWA"));
}

void ASwab::ApplyToBloodStain(ABloodStain* const Stain)
{
	if (Stain)
	{
		TArray<FEvidentialInfo> Infos;
		FEvidentialInfo Info(EEvidentialType::Blood, 0U);

		Infos.Add(Info);

		FEvidentialCapture Capture(EEvidentialMedium::Item, Infos);

		AddCapture(Capture);

		Stain->Disable();
	}
}

void ASwab::Clear()
{
	Destroy();
}
