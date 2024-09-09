// Fill out your copyright notice in the Description page of Project Settings.


#include "MoreMovementPlayerController.h"
#include "ProneCharacter.h"
#include "AdvancedAbilityComponent.h"
#include "AbilitySetupComponent.h"

void AMoreMovementPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	AProneCharacter* Char = Cast<AProneCharacter>(GetPawn());

	if (Char)
	{
		Char->GetAbilitySystemComponent()->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void AMoreMovementPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AProneCharacter* Char = Cast<AProneCharacter>(GetPawn());

	if (Char)
	{
		Char->GetAbilitySetupComponent()->AddInputMappingContext(GetLocalPlayer());
	}
}

void AMoreMovementPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	AProneCharacter* Char = Cast<AProneCharacter>(GetPawn());

	if (Char)
	{
		Char->GetAbilitySetupComponent()->InitializeAbilitySystem();
	}
}