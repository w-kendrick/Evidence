// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AWorldGenerator::AWorldGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->bHiddenInGame = false;
	Box->SetVisibility(true);
}

void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		SpawnClasses();
	}
}

void AWorldGenerator::SpawnClasses()
{
	for (const FEvidentialSpawn& SpawnClass : ClassesToSpawn)
	{
		const TSubclassOf<AActor>& Class = SpawnClass.Class;
		const float& Rate = SpawnClass.SpawnRate;

		const float& Area = Box->GetScaledBoxExtent().X * Box->GetScaledBoxExtent().Y;
		const int32 Count = FMath::RoundToInt(Area * Rate * FMath::Pow(10.0f, -8.0f));

		for (uint8 I = 0; I < Count; I++)
		{
			const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(Box->GetComponentLocation(), Box->GetScaledBoxExtent());
			SpawnClassAtLocation(Class, Location);
		}
	}
}

void AWorldGenerator::SpawnClassAtLocation(const TSubclassOf<AActor>& Class, const FVector& Location)
{
	FVector GroundPoint;

	if (GetGroundPoint(Location, GroundPoint))
	{
		const FTransform& Transform = FTransform(GroundPoint);

		FActorSpawnParameters Params;

		AActor* const Spawned = GetWorld()->SpawnActor<AActor>(Class, Transform, Params);
	}
}

bool AWorldGenerator::GetGroundPoint(const FVector& OriginalPoint, FVector& NewPoint) const
{
	bool bResult = false;
	NewPoint = OriginalPoint;

	FHitResult Hit;
	const FVector EndPoint = OriginalPoint - 10 * FVector::UpVector * Box->GetScaledBoxExtent().Z;
	if (GetWorld()->LineTraceSingleByChannel(Hit, OriginalPoint, EndPoint, ECollisionChannel::ECC_Visibility))
	{
		NewPoint = Hit.ImpactPoint;
		bResult = true;
	}

	return bResult;
}
