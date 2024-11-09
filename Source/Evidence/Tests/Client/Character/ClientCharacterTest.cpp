// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"
#include "EnhancedInputSubsystems.h"

bool AClientCharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));

	if (PlayerController)
	{
		TestCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());

		if (TestCharacter)
		{
			auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				AltClientTestCharacter = GetAltClientBaseCharacter();

				if (AltClientTestCharacter)
				{
					_bIsReady = true;

					checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
					checkf(TestCharacter != nullptr, TEXT("TestCharacter is invalid"));
					checkf(AltClientTestCharacter != nullptr, TEXT("AltClientTestCharacter is invalid"));
				}
			}
		}
	}

	return _bIsReady;
}

void AClientCharacterTest::InjectInput(const UInputAction* Action, FVector Value)
{
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};
	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}

ABaseCharacter* AClientCharacterTest::GetAltClientBaseCharacter() const
{
	ABaseCharacter* ReturnCharacter = nullptr;

	APlayerController* AltClientPlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));

	if (AltClientPlayerController)
	{
		TArray<AActor*> Actors;
		UMPTestHelpersBPLibrary::GetAllClientActorsOfClass(ABaseCharacter::StaticClass(), Actors, 1);

		for (AActor* Actor : Actors)
		{
			ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Actor);

			if (BaseCharacter != AltClientPlayerController->GetPawn())
			{
				ReturnCharacter = BaseCharacter;
			}
		}
	}

	return ReturnCharacter;
}
