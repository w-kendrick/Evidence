// Fill out your copyright notice in the Description page of Project Settings.


#include "Swab.h"

ASwab::ASwab()
{
	MaxCaptures = 1;
}

void ASwab::ApplyToBloodStain(ABloodStain* const Stain)
{
	TArray<FEvidentialInfo> Infos;
	FEvidentialInfo Info(EEvidentialType::Blood, 0U);

	Infos.Add(Info);

	FEvidentialCapture Capture(EEvidentialMedium::Item, Infos);

	AddCapture(Capture);
}
