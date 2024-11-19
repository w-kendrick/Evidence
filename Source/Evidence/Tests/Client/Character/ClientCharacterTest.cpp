// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCharacterTest.h"

AClientCharacterTest::AClientCharacterTest()
{
	bTestHasBegun = false;

	bClient1Passed = false;
	bClient2Passed = false;
}

void AClientCharacterTest::StartTest()
{
	Super::StartTest();

	GetOtherClient(0, Client1TestInfo);
	GetOtherClient(1, Client2TestInfo);
}

bool AClientCharacterTest::IsReady_Implementation()
{
	bool bReady = false;

	bReady = IsPlayerReady(0, Client1TestInfo) && IsPlayerReady(1, Client2TestInfo);

	if (bReady)
	{
		bTestHasBegun = true;
	}

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
				PlayerTestInfo.MyCharacter = Character;
				PlayerTestInfo.InputSubsystem = InputSubsystem;
			}
		}
	}

	return bPlayerReady;
}

void AClientCharacterTest::GetOtherClient(const uint8 PlayerIndex, FPlayerTestInfo& PlayerTestInfo) const
{
	TArray<AActor*> Actors;
	UMPTestHelpersBPLibrary::GetAllClientActorsOfClass(ABaseCharacter::StaticClass(), Actors, PlayerIndex);;

	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character != PlayerTestInfo.MyCharacter)
		{
			PlayerTestInfo.OtherCharacter = Character;
		}
	}
}

void AClientCharacterTest::BindTriggers()
{
	TriggerBox1 = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATriggerBox::StaticClass(), 0));
	if (TriggerBox1)
	{
		TriggerBox1->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger1BeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerBox1 is invalid"))
	}

	TriggerBox2 = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATriggerBox::StaticClass(), 1));
	if (TriggerBox2)
	{
		TriggerBox2->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger2BeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerBox2 is invalid"))
	}
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
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Client 1 %s"), bClient1Passed ? "pass" : "fail")
		UE_LOG(LogTemp, Display, TEXT("Client 2 %s"), bClient2Passed ? "pass" : "fail")
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
