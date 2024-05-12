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
