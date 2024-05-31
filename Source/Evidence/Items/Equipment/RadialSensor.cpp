// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialSensor.h"
#include "Evidence/Evidence.h"

ARadialSensor::ARadialSensor()
{
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
	PowerComponent->ActiveDrainRate = 0.1f;

	SenseDelay = 3.0f;
	SenseRadius = 1000.f;
}

UPowerComponent* ARadialSensor::GetPowerComponent() const
{
	return PowerComponent;
}

void ARadialSensor::Activate()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SenseHandle, this, &ThisClass::Sense, SenseDelay, true, SenseDelay);
	}
}

void ARadialSensor::Deactivate()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().ClearTimer(SenseHandle);
	}
}

void ARadialSensor::Sense()
{
	TArray<FVector> Output;

	DrawDebugSphere(GetWorld(), GetActorLocation(), SenseRadius, 6, FColor::Blue, false, 3.0f);

	TArray<FOverlapResult> Overlaps;
	if (GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), GetActorRotation().Quaternion(), COLLISION_SENSE, FCollisionShape::MakeSphere(SenseRadius)))
	{
		for (const FOverlapResult& Overlap : Overlaps)
		{
			const FVector Relative = (Overlap.GetActor()->GetActorLocation() - GetActorLocation()) / SenseRadius;
			Output.Add(Relative);
		}
		OnRadialSense.Broadcast(this, Output);
	}

	OnRadialSense.Broadcast(this, TArray<FVector>());
}
