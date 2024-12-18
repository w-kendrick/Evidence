// Copyright Epic Games, Inc. All Rights Reserved.


#include "EvidencePlayerController.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "EnhancedInputSubsystems.h"
#include "Evidence/HUD/EvidenceHUD.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"

void AEvidencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	AEvidenceGameState* const EvidenceGameState = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EvidenceGameState)
	{
		EvidenceGameState->OnCandidateSpectateesChanged.AddUObject(this, &ThisClass::OnCandidateSpectateesChanged);
	}
}

void AEvidencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (SwitchSpectateeAction)
		{
			EnhancedInputComponent->BindAction(SwitchSpectateeAction, ETriggerEvent::Started, this, &ThisClass::SwitchSpectatee);
		}
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

void AEvidencePlayerController::ClientSetLockerWidgetVisibility_Implementation(const bool bVisibility)
{
	OnSetLockerWidgetVisibility.ExecuteIfBound(bVisibility);
}

void AEvidencePlayerController::SetInteractWidgetVisibility(const bool bVisibility, const float Duration, const FString& DisplayString)
{
	OnSetInteractWidgetVisibility.ExecuteIfBound(bVisibility, Duration, DisplayString);
}

void AEvidencePlayerController::SetInteractTimerState(const bool bState, const float Duration)
{
	OnInteractTimerStateChanged.ExecuteIfBound(bState, Duration);
}

#pragma region Spectating

void AEvidencePlayerController::ClientSetIsSpectating_Implementation(const bool bInIsSpectating)
{
	bIsSpectating = bInIsSpectating;
	OnSpectatingChanged.Broadcast(bIsSpectating);

	if (bIsSpectating)
	{
		SpectateNext();
	}
	else
	{
		SetViewTarget(GetPawn());
	}
}

void AEvidencePlayerController::SwitchSpectatee(const FInputActionValue& Value)
{
	if (bIsSpectating)
	{
		const float Direction = Value.Get<float>();
		if (Direction > 0)
		{
			SpectateNext();
		}
		else if (Direction < 0)
		{
			SpectatePrevious();
		}
	}
}

void AEvidencePlayerController::OnCandidateSpectateesChanged(FSpectateeList& SpectateeList)
{
	CandidateSpectatees.Empty();

	for (uint8 Index = 0; Index < SpectateeList.GetNum(); Index++)
	{
		const FSpectateeItem& Entry = SpectateeList[Index];

		if (Entry.GetSpectatee() != GetPawn())
		{
			CandidateSpectatees.AddEntry(Entry);
		}
	}

	if (SpectateIndex >= CandidateSpectatees.GetNum())
	{
		SpectateNext();
	}
}

void AEvidencePlayerController::SpectateNext()
{
	if (CandidateSpectatees.GetNum() > 0)
	{
		const int32 NewSpectateIndex = (SpectateIndex + 1) % CandidateSpectatees.GetNum();
		SpectateIndex = NewSpectateIndex;
		UpdateSpectatee();
	}
}

void AEvidencePlayerController::SpectatePrevious()
{
	if (CandidateSpectatees.GetNum() > 0)
	{
		int32 NewSpectateIndex = SpectateIndex - 1;
		if (NewSpectateIndex < 0)
		{
			NewSpectateIndex += CandidateSpectatees.GetNum();
		}
		SpectateIndex = NewSpectateIndex;
		UpdateSpectatee();
	}
}

void AEvidencePlayerController::UpdateSpectatee()
{
	if (SpectateIndex < CandidateSpectatees.GetNum())
	{
		const FSpectateeItem& Entry = CandidateSpectatees[SpectateIndex];
		APawn* const SpectateePawn = Entry.GetSpectatee();

		OnSpectateeChanged.Broadcast(SpectateePawn);
		SetViewTarget(SpectateePawn);
	}
}

#pragma endregion