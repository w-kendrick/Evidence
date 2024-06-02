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

bool AClaymore::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	if (isPlanted)
	{
		return false;
	}
	else
	{
		return Super::IsAvailableForInteraction_Implementation(InteractionComponent);
	}
}

void AClaymore::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->Deactivate();
	if (HasAuthority())
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	}
}

void AClaymore::Plant()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Plant claymore");
	PerceptionComponent->Activate();
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Boom");
	Destroy();
}
