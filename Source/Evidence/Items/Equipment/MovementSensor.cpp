// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSensor.h"

AMovementSensor::AMovementSensor()
{
	SenseDelay = 3.0f;
	ActiveDrainRate = 0.1f;
}

void AMovementSensor::Activate()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SenseHandle, this, &ThisClass::Sense, SenseDelay, true, SenseDelay);
	}
}

void AMovementSensor::Deactivate()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().ClearTimer(SenseHandle);
	}
}

void AMovementSensor::Sense()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Sense");
}
