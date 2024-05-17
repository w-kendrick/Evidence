// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Net/UnrealNetwork.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Evidence/Interfaces/Evidential.h"
#include "Evidence/Structs/EvidentialInfo.h"

ACamera::ACamera()
{
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(LocalMesh);
	SceneCaptureComponent->MaxViewDistanceOverride = 200.f;
	SceneCaptureComponent->FOVAngle = 90.f;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->PeripheralVisionAngleDegrees = 45.f;
	Sight->SightRadius = 200.f;
	Sight->LoseSightRadius = 200.f;

	PerceptionComponent->ConfigureSense(*Sight);
}

void ACamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACamera, Captures);
}

void ACamera::SaveFrame()
{
	TArray<FHitResult> Hits;
	const FQuat Rot = SceneCaptureComponent->GetComponentQuat();
	const FVector BoxExtent = FVector(SceneCaptureComponent->MaxViewDistanceOverride,
		SceneCaptureComponent->MaxViewDistanceOverride * FMath::Cos(FMath::DegreesToRadians(SceneCaptureComponent->FOVAngle * 0.5f)) * 2.f,
		SceneCaptureComponent->MaxViewDistanceOverride * FMath::Cos(FMath::DegreesToRadians(SceneCaptureComponent->FOVAngle * 0.5f)) * 2.f);

	const FVector Loc = SceneCaptureComponent->GetComponentLocation() + SceneCaptureComponent->GetForwardVector() * SceneCaptureComponent->MaxViewDistanceOverride;

	const FCollisionShape Shape = FCollisionShape::MakeBox(BoxExtent);

	DrawDebugBox(GetWorld(), Loc, BoxExtent, Rot, FColor::Red, true, -1.0f, 0, 5.0f);

	TArray<FEvidentialInfo> CapturedEvidentials;

	if (GetWorld()->SweepMultiByChannel(Hits, Loc, Loc, Rot, ECollisionChannel::ECC_Visibility, Shape))
	{
		for (const FHitResult Hit : Hits)
		{
			IEvidential* const Evidential = Cast<IEvidential>(Hit.GetActor());
			if (Evidential)
			{
				const FEvidentialInfo Info = FEvidentialInfo(Evidential->GetType(), Evidential->GetBaseWorth());
				CapturedEvidentials.Add(Info);
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString("Pictured count: ") + FString::FromInt(CapturedEvidentials.Num()));
	const FEvidentialCapture Capture = FEvidentialCapture(EEvidentialMedium::Photo, CapturedEvidentials);
	Captures.Add(Capture);
}
