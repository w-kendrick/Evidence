// Copyright Epic Games, Inc. All Rights Reserved.


#include "EvidencePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/EvidenceCharacter.h"

void AEvidencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void AEvidencePlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	AEvidenceCharacter* Char = Cast<AEvidenceCharacter>(P);
	if (Char)
	{
		Char->GetAbilitySystemComponent()->InitAbilityActorInfo(Char, Char);
	}
}
