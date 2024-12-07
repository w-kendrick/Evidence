// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialSensor.h"
#include "Evidence/Evidence.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Hub/Hub.h"

ARadialSensor::ARadialSensor()
{
	SenseDelay = 3.0f;
	SenseRadius = 1000.f;

	EquipmentAbbreviation = FString(TEXT("RSE"));
}

void ARadialSensor::BeginPlay()
{
	Super::BeginPlay();

	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	if (Hub)
	{
		Hub->RegisterRadialSensor(this);
	}
}

void ARadialSensor::ActivatePower()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SenseHandle, this, &ThisClass::Sense, SenseDelay, true, SenseDelay);
	}
}

void ARadialSensor::DeactivatePower()
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
