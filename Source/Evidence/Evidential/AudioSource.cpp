// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSource.h"
#include "Perception/AISense_Hearing.h"

AAudioSource::AAudioSource()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAudioSource::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &ThisClass::PlayAudio, 2.f, true);
	}
}

void AAudioSource::PlayAudio()
{
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 100, this, 1000, FName());
}

EEvidentialType AAudioSource::GetType() const
{
	return EEvidentialType::Alien;
}

float AAudioSource::GetBaseWorth() const
{
	return 0.0f;
}
