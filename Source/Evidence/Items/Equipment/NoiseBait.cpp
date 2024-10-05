// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseBait.h"
#include "Perception/AISense_Hearing.h"

ANoiseBait::ANoiseBait()
{
	EventDelay = 2.5f;
}

void ANoiseBait::ActivatePower()
{
	GetWorldTimerManager().SetTimer(SoundHandle, this, &ThisClass::SoundEvent, EventDelay, true);
}

void ANoiseBait::DeactivatePower()
{
	GetWorldTimerManager().ClearTimer(SoundHandle);
}

void ANoiseBait::SoundEvent()
{
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 100, this, 1000, FName());
	MulticastSoundEffect();
}

void ANoiseBait::MulticastSoundEffect_Implementation()
{
}
