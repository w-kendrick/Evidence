// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTest.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"

bool ACharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	APlayerController* const _PlayerController = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerController::StaticClass()));

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

				checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
				checkf(BaseCharacter != nullptr, TEXT("BaseCharacter is invalid"));
			}
		}
	}

	return _bIsReady;
}

void ACharacterTest::InjectInput(const UInputAction* Action, FVector Value)
{
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	TArray<UInputModifier*> Modifiers;
	TArray<UInputTrigger*> Triggers;
	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}
