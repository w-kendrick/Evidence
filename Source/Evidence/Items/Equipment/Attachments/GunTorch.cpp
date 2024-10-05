// Fill out your copyright notice in the Description page of Project Settings.


#include "GunTorch.h"
#include "Components/SpotLightComponent.h"

AGunTorch::AGunTorch()
{
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(WorldMesh);
	LightComponent->OuterConeAngle = 20.0f;
	LightComponent->IntensityUnits = ELightUnits::Unitless;
	LightComponent->SetVisibility(false);

	EquipmentName = FString(TEXT("GunTorch"));
}

void AGunTorch::Activate()
{
	LightComponent->SetVisibility(true);
}

void AGunTorch::Deactivate()
{
	LightComponent->SetVisibility(false);
}
