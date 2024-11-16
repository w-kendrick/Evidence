// Fill out your copyright notice in the Description page of Project Settings.


#include "Claymore.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

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

bool AClaymore::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const
{
	if (isPlanted)
	{
		return false;
	}
	else
	{
		return Super::IsAvailableForInteraction_Implementation(InteractionComponent, InteractingActor);
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
	Super::Plant();
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
	if (isPlanted)
	{
		Detonate();
	}
}

void AClaymore::Detonate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Boom");

	TArray<AActor*> OutActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), OutActors);

	for (AActor* const Actor : OutActors)
	{
		const float Damage = CalculateDamage(Actor->GetActorLocation());

		const IAbilitySystemInterface* const AS = Cast<IAbilitySystemInterface>(Actor);

		if (AS)
		{
			UAbilitySystemComponent* const ASC = AS->GetAbilitySystemComponent();

			if (ASC)
			{
				ASC->ApplyGameplayEffectSpecToSelf(*DamageEffectHandle.Data);
			}
		}
	}

	Destroy();
}

float AClaymore::CalculateDamage(const FVector Location) const
{
	const FVector Delta = Location - GetActorLocation();

	return Delta.Size();
}
