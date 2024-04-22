// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
#include "Kismet/GameplayStatics.h"

AHub* AEvidenceGameState::GetHub()
{
	if (Hub)
	{
		return Hub;
	}

	Hub = Cast<AHub>(UGameplayStatics::GetActorOfClass(GetWorld(), AHub::StaticClass()));
	return Hub;
}
