// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTest.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"

bool ACharacterTest::IsReady_Implementation()
{
	bool _bIsReady = false;

	const APlayerController* const _PlayerController = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerController::StaticClass()));

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

void ACharacterTest::StartTest()
{
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerController::StaticClass()));
	BaseCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());

	checkf(PlayerController != nullptr, TEXT("PlayerController is invalid"));
}

void ACharacterTest::InjectInput(const UInputAction* Action, FVector Value)
{
	auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	TArray<UInputModifier*> Modifiers;
	TArray<UInputTrigger*> Triggers;
	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}
