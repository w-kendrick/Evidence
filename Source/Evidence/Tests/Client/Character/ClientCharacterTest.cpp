// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"

AClientCharacterTest::AClientCharacterTest()
{
	bClient1Passed = false;
	bClient2Passed = false;
}

bool AClientCharacterTest::IsReady_Implementation()
{
	bool bReady = false;

	bReady = IsPlayerReady(0, Client1TestInfo) && IsPlayerReady(1, Client2TestInfo);

	return bReady;
}

bool AClientCharacterTest::IsPlayerReady(const uint8 PlayerIndex, FPlayerTestInfo& PlayerTestInfo) const
{
	bool bPlayerReady = false;

	APlayerController* const PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), PlayerIndex));

	if (PlayerController)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerController->GetPawn());

		if (Character)
		{
			UEnhancedInputLocalPlayerSubsystem* const InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				bPlayerReady = true;

				PlayerTestInfo.PlayerController = PlayerController;
				PlayerTestInfo.Character = Character;
				PlayerTestInfo.InputSubsystem = InputSubsystem;
			}
		}
	}

	return bPlayerReady;
}

void AClientCharacterTest::BindTriggers()
{
	ATriggerBox* TriggerBox1 = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 0));
	TriggerBox1->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger1BeginOverlap);

	ATriggerBox* TriggerBox2 = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), 1));
	TriggerBox2->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger2BeginOverlap);
}

void AClientCharacterTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	
}

void AClientCharacterTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	
}

void AClientCharacterTest::CheckResult()
{
	if (bClient1Passed && bClient2Passed)
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
}

void AClientCharacterTest::InjectInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}

void AClientCharacterTest::StartInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->StartContinuousInputInjectionForAction(Action, Value, Modifiers, Triggers);
}

void AClientCharacterTest::StopInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->StopContinuousInputInjectionForAction(Action);
}
