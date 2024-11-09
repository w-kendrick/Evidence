// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"
#include "MPTestHelpersBPLibrary.h"
#include "EnhancedInputSubsystems.h"

bool AClientCharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	APlayerController* const _PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));

	if (_PlayerController)
	{
		APawn* const Pawn = _PlayerController->GetPawn();

		if (Pawn)
		{
			auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				_bIsReady = true;

				PlayerController = _PlayerController;
				BaseCharacter = Cast<ABaseCharacter>(Pawn);
				//AltClientBaseCharacter = Cast<ABaseCharacter>(UMPTestHelpersBPLibrary::GetClientActorOfClassWithTag(ABaseCharacter::StaticClass(), FName("TestCharacter"), 1));

				checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
				checkf(BaseCharacter != nullptr, TEXT("BaseCharacter is invalid"));
				checkf(AltClientBaseCharacter != nullptr, TEXT("AltClientBaseCharacter is invalid"));
			}
		}
	}

	return _bIsReady;
}

void AClientCharacterTest::InjectInput(const UInputAction* Action, FVector Value)
{
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	TArray<UInputModifier*> Modifiers;
	TArray<UInputTrigger*> Triggers;
	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}
