// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoCamera.h"
#include "Evidence/Evidence.h"
#include "Perception/AISenseConfig_Sight.h"

AAutoCamera::AAutoCamera()
{
	SenseDelay = 3.0f;
	SenseRadius = 1000.f;

	EquipmentAbbreviation = FString(TEXT("ACM"));
}

void AAutoCamera::StartSensing()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SenseHandle, this, &ThisClass::Sense, SenseDelay, true, SenseDelay);
	}
}

void AAutoCamera::StopSensing()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().ClearTimer(SenseHandle);
	}
}


void AAutoCamera::Sense()
{
	TArray<FVector> Output;

	DrawDebugSphere(GetWorld(), GetActorLocation(), SenseRadius, 6, FColor::Blue, false, 3.0f);

	FVector LookPoint;
	FRotator LookRot;
	GetActorEyesViewPoint(LookPoint, LookRot);

	TArray<FOverlapResult> Overlaps;
	if (GetWorld()->OverlapMultiByChannel(Overlaps, LookPoint, GetActorRotation().Quaternion(), COLLISION_SENSE, FCollisionShape::MakeSphere(SenseRadius)))
	{
		for (const FOverlapResult& Overlap : Overlaps)
		{
			const FVector Relative = (Overlap.GetActor()->GetActorLocation() - LookPoint) / SenseRadius;
			if (GetAngleBetweenVectors(Relative, LookRot.Vector()) < Sight->PeripheralVisionAngleDegrees)
			{
				Output.Add(Relative);
			}
		}
	}

	if (Output.Num() != PreviousSense.Num())
	{
		MovementSensed();
	}
	else if (Output.Num() > 0)
	{
		if (!doArraysMatch(PreviousSense, Output))
		{
			MovementSensed();
		}
	}

	PreviousSense = Output;
}

float AAutoCamera::GetAngleBetweenVectors(const FVector& Vec1, const FVector& Vec2) const
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Vec1, Vec2) / (Vec1.Size() * Vec2.Size())));
}

bool AAutoCamera::doArraysMatch(const TArray<FVector>& Arr1, const TArray<FVector>& Arr2) const
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

void AAutoCamera::MovementSensed()
{
	if (HasAuthority())
	{
		SaveFrame();
		TakePhoto();
	}
}
