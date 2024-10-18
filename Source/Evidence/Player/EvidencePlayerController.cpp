// Copyright Epic Games, Inc. All Rights Reserved.


#include "EvidencePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Evidence/HUD/EvidenceHUD.h"

void AEvidencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void AEvidencePlayerController::ClientSetInputEnabled_Implementation(const bool bEnabled)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		if (bEnabled)
		{
			MyPawn->EnableInput(this);
		}
		else
		{
			MyPawn->DisableInput(this);
		}
	}
}

void AEvidencePlayerController::ClientSetTerminalMenuVisibility_Implementation(const bool bVisibility)
{
	OnSetTerminalMenuVisibility.ExecuteIfBound(bVisibility);
}

void AEvidencePlayerController::ClientSetAttachmentWidgetVisibility_Implementation(const bool bVisibility)
{
	OnSetAttachmentWidgetVisibility.ExecuteIfBound(bVisibility);
}

void AEvidencePlayerController::SetInteractWidgetVisibility(const bool bVisibility, const float Duration, const FString& DisplayString)
{
	OnSetInteractWidgetVisibility.ExecuteIfBound(bVisibility, Duration, DisplayString);
}

void AEvidencePlayerController::SetInteractTimerState(const bool bState, const float Duration)
{
	OnInteractTimerStateChanged.ExecuteIfBound(bState, Duration);
}
