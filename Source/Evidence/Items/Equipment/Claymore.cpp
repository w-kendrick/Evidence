// Fill out your copyright notice in the Description page of Project Settings.


#include "Claymore.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AClaymore::AClaymore()
{
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

void AClaymore::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	}
}

void AClaymore::Plant()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Plant claymore");
}

void AClaymore::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	FRotator Rot;
	Super::GetActorEyesViewPoint(OutLocation, Rot);

	OutRotation = GetActorRightVector().Rotation();
}

void AClaymore::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Detonate();
}

void AClaymore::Detonate()
{
}
