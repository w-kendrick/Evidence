// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseBait.h"
#include "Perception/AISense_Hearing.h"

ANoiseBait::ANoiseBait()
{
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));

	EventDelay = 2.5f;
}

UPowerComponent* ANoiseBait::GetPowerComponent() const
{
	return PowerComponent;
}

void ANoiseBait::Activate()
{
	GetWorldTimerManager().SetTimer(SoundHandle, this, &ThisClass::SoundEvent, EventDelay, true);
}

void ANoiseBait::Deactivate()
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
