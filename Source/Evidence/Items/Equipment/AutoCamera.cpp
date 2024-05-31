// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoCamera.h"

AAutoCamera::AAutoCamera()
{
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
	PowerComponent->ActiveDrainRate = 0.1f;
}

UPowerComponent* AAutoCamera::GetPowerComponent() const
{
	return PowerComponent;
}

void AAutoCamera::Activate()
{
}

void AAutoCamera::Deactivate()
{
}
