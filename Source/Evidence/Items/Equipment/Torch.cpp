// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"
#include "Components/SpotLightComponent.h"

ATorch::ATorch()
{
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(WorldMesh);
	LightComponent->OuterConeAngle = 20.0f;
	LightComponent->IntensityUnits = ELightUnits::Unitless;
	LightComponent->SetVisibility(false);

	PowerComponent = CreateDefaultSubobject<UPowerComponent>(TEXT("PowerComponent"));

	EquipmentName = FString(TEXT("Torch"));
}

UPowerComponent* ATorch::GetPowerComponent() const
{
	return PowerComponent;
}

void ATorch::Activate()
{
	LightComponent->SetVisibility(true);
}

void ATorch::Deactivate()
{
	LightComponent->SetVisibility(false);
}
