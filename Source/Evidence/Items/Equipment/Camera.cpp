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
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*Sight);
}

void ACamera::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	FRotator Rot;
	Super::GetActorEyesViewPoint(OutLocation, Rot);

	OutRotation = GetActorRightVector().Rotation();
}

TArray<FEvidentialInfo> ACamera::CaptureFrame()
{
	TArray<FEvidentialInfo> CapturedEvidentials;

	TArray<AActor*> OutActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), OutActors);

	for (const AActor* const Actor : OutActors)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, Actor->GetName());
		const IEvidential* const Evidential = Cast<IEvidential>(Actor);
		if (Evidential)
		{
			const FEvidentialInfo Info = FEvidentialInfo(Evidential->GetType(), GetFrameIndex());
			CapturedEvidentials.Add(Info);
		}
	}
	
	return CapturedEvidentials;
}

uint8 ACamera::GetFrameIndex() const
{
	return 0;
}