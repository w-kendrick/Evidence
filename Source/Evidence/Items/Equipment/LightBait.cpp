// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBait.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/PointLightComponent.h"

ALightBait::ALightBait()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));

	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(WorldMesh);
	LightComponent->IntensityUnits = ELightUnits::Unitless;
	LightComponent->SetVisibility(false);

	EventDelay = 0.5f;

	EquipmentAbbreviation = FString(TEXT("LBA"));
}

void ALightBait::BeginPlay()
{
	Super::BeginPlay();

	Stimulus->RegisterForSense(UAISense_Sight::StaticClass());
	Stimulus->RegisterWithPerceptionSystem();
	Stimulus->SetActive(false);
}

void ALightBait::ActivatePower()
{
	GetWorldTimerManager().SetTimer(StrobeHandle, this, &ThisClass::StrobeEvent, EventDelay, true);
}

void ALightBait::DeactivatePower()
{
	GetWorldTimerManager().ClearTimer(StrobeHandle);

	if (HasAuthority())
	{
		MulticastSynchronise(false);
	}
}

void ALightBait::StrobeEvent()
{
	LightComponent->ToggleVisibility();

	if (HasAuthority())
	{
		if (LightComponent->IsVisible())
		{
			Stimulus->SetActive(true);
		}
		else
		{
			Stimulus->SetActive(false);
		}
	}
}

void ALightBait::MulticastSynchronise_Implementation(const bool State)
{
	LightComponent->SetVisibility(State);
	Stimulus->SetActive(false);
}
