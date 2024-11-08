// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"
#include "MPTestHelpersBPLibrary.h"
#include "EnhancedInputSubsystems.h"

bool AClientCharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	const APlayerController* const _PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));

	if (_PlayerController)
	{
		const APawn* const Pawn = _PlayerController->GetPawn();

		if (Pawn)
		{
			_bIsReady = true;
		}
	}

	return _bIsReady;
}

void AClientCharacterTest::StartTest()
{
	PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));
	BaseCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());

	checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
}

void AClientCharacterTest::InjectInput(const UInputAction* Action, FVector Value)
{
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	TArray<UInputModifier*> Modifiers;
	TArray<UInputTrigger*> Triggers;
	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}
