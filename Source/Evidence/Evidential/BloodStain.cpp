// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodStain.h"
#include "Components/BoxComponent.h"

ABloodStain::ABloodStain()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->bHiddenInGame = false;
	Box->SetVisibility(true);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	RootComponent = Box;

	PrimaryActorTick.bCanEverTick = false;

}

EEvidentialType ABloodStain::GetType() const
{
	return EEvidentialType::Blood;
}

float ABloodStain::GetBaseWorth() const
{
	return 0.0f;
}
