// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSource.h"

AAudioSource::AAudioSource()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);

	Type = EEvidentialType::Alien;
	Lifetime = 1.f;
	AudibleRange = 100.f;
}

void AAudioSource::SetLifetime(const float NewLifetime)
{
	Lifetime = NewLifetime;

	GetWorldTimerManager().SetTimer(LifeHandle, this, &ThisClass::EndLife, Lifetime, false);
}

void AAudioSource::EndLife()
{
	Destroy();
}
