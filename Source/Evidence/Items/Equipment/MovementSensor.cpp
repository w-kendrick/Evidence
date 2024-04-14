// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSensor.h"

AMovementSensor::AMovementSensor()
{
	SenseDelay = 3.0f;
	SenseRadius = 1000.f;
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
	TArray<FVector> Output;

	DrawDebugSphere(GetWorld(), GetActorLocation(), SenseRadius, 6, FColor::Blue, false, 3.0f);

	TArray<FOverlapResult> Overlaps;
	if (GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), GetActorRotation().Quaternion(), ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(SenseRadius)))
	{
		for (FOverlapResult& Overlap : Overlaps)
		{
			const FVector Relative = Overlap.GetActor()->GetActorLocation() - GetActorLocation();
			Output.Add(Relative);
			OnSense.Broadcast(Output);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Sensed: ") + FString::FromInt(Output.Num()));
}
