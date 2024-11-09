// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"
#include "EnhancedInputSubsystems.h"

bool AClientCharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));

	if (PlayerController)
	{
		BaseCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());

		if (BaseCharacter)
		{
			auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				_bIsReady = true;;

				checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
				checkf(BaseCharacter != nullptr, TEXT("BaseCharacter is invalid"));
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
