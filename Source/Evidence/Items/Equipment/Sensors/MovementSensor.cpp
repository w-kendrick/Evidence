// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSensor.h"
#include "Evidence/Evidence.h"

AMovementSensor::AMovementSensor()
{
	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));
	PowerComponent->ActiveDrainRate = 0.1f;

	SenseDelay = 3.0f;
	SenseRadius = 1000.f;
}

UPowerComponent* AMovementSensor::GetPowerComponent() const
{
	return PowerComponent;
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
	}

	if (Output.Num() != PreviousSense.Num())
	{
		OnMovementSense.Broadcast(this);
	}
	else if (Output.Num() > 0)
	{
		if (!doArraysMatch(PreviousSense, Output))
		{
			OnMovementSense.Broadcast(this);
		}
	}

	PreviousSense = Output;
}

bool AMovementSensor::doArraysMatch(const TArray<FVector>& Arr1, const TArray<FVector>& Arr2) const
{
	TArray<bool> VectorMatched;

	for (uint8 i = 0; i < Arr2.Num(); i++)
	{
		VectorMatched.Add(false);
	}

	for (const FVector Vec1 : Arr1)
	{
		bool isMatched = false;
		uint8 Index = 0;

		while (!isMatched && Index < Arr2.Num())
		{
			const FVector Vec2 = Arr2[Index];

			if ((Vec1 - Vec2).IsNearlyZero() && !VectorMatched[Index])
			{
				isMatched = true;
				VectorMatched[Index] = true;
			}
			Index++;
		}

		if (!isMatched)
		{
			return false;
		}
	}

	return true;
}
