// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityActor.h"
#include "AbilitySystemComponent.h"

AAbilityActor::AAbilityActor()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AAbilityActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
