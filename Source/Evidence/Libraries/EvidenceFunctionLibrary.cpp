// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Hub/Hub.h"

AHub* UEvidenceFunctionLibrary::GetHub(UWorld* World)
{
	return Cast<AHub>(UGameplayStatics::GetActorOfClass(World, AHub::StaticClass()));;
}
