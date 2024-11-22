// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTest.h"
#include "GameFramework/PlayerState.h"

ACharacterTest::ACharacterTest()
{
	bTestHasBegun = false;

	bServerPassed = false;
	bClient1Passed = false;
	bClient2Passed = false;
}

void ACharacterTest::StartTest()
{
	Super::StartTest();

	ServerGetOtherPlayers();
	ClientGetOtherPlayers(0, Client1TestInfo, Client2PlayerId);
	ClientGetOtherPlayers(1, Client2TestInfo, Client1PlayerId);

	UE_LOG(LogTemp, Display, TEXT("ServerPlayerId: %d"), ServerPlayerId);
	UE_LOG(LogTemp, Display, TEXT("Client1PlayerId: %d"), Client1PlayerId);
	UE_LOG(LogTemp, Display, TEXT("Client2PlayerId: %d"), Client2PlayerId);

	UE_LOG(LogTemp, Display, TEXT("Server Myself: %d"), ServerTestInfo.MyCharacter->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Server Client1: %d"), ServerTestInfo.Client1Character->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Server Client2: %d"), ServerTestInfo.Client2Character->GetPlayerState()->GetPlayerId());

	UE_LOG(LogTemp, Display, TEXT("Client1 Myself: %d"), Client1TestInfo.MyCharacter->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Client1 Server: %d"), Client1TestInfo.ServerCharacter->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Client1 Other Client: %d"), Client1TestInfo.OtherClientCharacter->GetPlayerState()->GetPlayerId());

	UE_LOG(LogTemp, Display, TEXT("Client2 Myself: %d"), Client2TestInfo.MyCharacter->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Client2 Server: %d"), Client2TestInfo.ServerCharacter->GetPlayerState()->GetPlayerId());
	UE_LOG(LogTemp, Display, TEXT("Client2 Other Client: %d"), Client2TestInfo.OtherClientCharacter->GetPlayerState()->GetPlayerId());
}

bool ACharacterTest::IsReady_Implementation()
{
	bool bReady = true;

	bReady &= IsServerReady();
	bReady &= IsClientReady(0, Client1TestInfo, Client1PlayerId);
	bReady &= IsClientReady(1, Client2TestInfo, Client2PlayerId);

	if (bReady)
	{
		bTestHasBegun = true;
	}

	return bReady;
}

bool ACharacterTest::IsServerReady()
{
	bool bMyselfReady = false;

	APlayerController* const PlayerController = Cast<APlayerController>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerController::StaticClass()));

	if (PlayerController)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerController->GetPawn());

		if (Character)
		{
			UEnhancedInputLocalPlayerSubsystem* const InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				APlayerState* PlayerState = Character->GetPlayerState();

				if (PlayerState)
				{
					bMyselfReady = true;

					ServerTestInfo.PlayerController = PlayerController;
					ServerTestInfo.MyCharacter = Character;
					ServerTestInfo.InputSubsystem = InputSubsystem;

					ServerPlayerId = PlayerState->GetPlayerId();
				}
			}
		}
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Actors);
	uint8 ReadyCount = 0;
	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character)
		{
			APlayerState* PlayerState = Character->GetPlayerState();

			if (PlayerState)
			{
				ReadyCount++;
			}
		}
	}

	return bMyselfReady && (ReadyCount == 3);
}

bool ACharacterTest::IsClientReady(const uint8 PlayerIndex, FClientTestInfo& ClientTestInfo, int32& ClientId) const
{
	bool bMyselfReady = false;

	APlayerController* const PlayerController = Cast<APlayerController>(UMPTestHelpersBPLibrary::GetClientActorOfClass(APlayerController::StaticClass(), PlayerIndex));

	if (PlayerController)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerController->GetPawn());

		if (Character)
		{
			UEnhancedInputLocalPlayerSubsystem* const InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

			if (InputSubsystem)
			{
				APlayerState* PlayerState = Character->GetPlayerState();

				if (PlayerState)
				{
					bMyselfReady = true;

					ClientTestInfo.PlayerController = PlayerController;
					ClientTestInfo.MyCharacter = Character;
					ClientTestInfo.InputSubsystem = InputSubsystem;

					ClientId = PlayerState->GetPlayerId();
				}
			}
		}
	}

	TArray<AActor*> Actors;
	UMPTestHelpersBPLibrary::GetAllClientActorsOfClass(ABaseCharacter::StaticClass(), Actors, PlayerIndex);
	uint8 ReadyCount = 0;
	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character)
		{
			APlayerState* PlayerState = Character->GetPlayerState();

			if (PlayerState)
			{
				ReadyCount++;
			}
		}
	}

	return bMyselfReady && (ReadyCount == 3);
}

void ACharacterTest::ServerGetOtherPlayers()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character->GetPlayerState()->GetPlayerId() == Client1PlayerId)
		{
			ServerTestInfo.Client1Character = Character;
		}

		if (Character->GetPlayerState()->GetPlayerId() == Client2PlayerId)
		{
			ServerTestInfo.Client2Character = Character;
		}
	}
}

void ACharacterTest::ClientGetOtherPlayers(const uint8 PlayerIndex, FClientTestInfo& ClientTestInfo, const int32 OtherClientId) const
{
	TArray<AActor*> Actors;
	UMPTestHelpersBPLibrary::GetAllClientActorsOfClass(ABaseCharacter::StaticClass(), Actors, PlayerIndex);

	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character->GetPlayerState()->GetPlayerId() == ServerPlayerId)
		{
			ClientTestInfo.ServerCharacter = Character;
		}

		if (Character->GetPlayerState()->GetPlayerId() == OtherClientId)
		{
			ClientTestInfo.OtherClientCharacter = Character;
		}
	}
}

void ACharacterTest::BindTriggers()
{
	ServerTriggerBox = Cast<ATriggerBox>(UGameplayStatics::GetActorOfClass(GetWorld(), ATriggerBox::StaticClass()));
	if (ServerTriggerBox)
	{
		ServerTriggerBox->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnServerTriggerBeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ServerTriggerBox is invalid"))
	}

	Client1TriggerBox = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATriggerBox::StaticClass(), 0));
	if (Client1TriggerBox)
	{
		Client1TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnClient1TriggerBeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Client1TriggerBox is invalid"))
	}

	Client2TriggerBox = Cast<ATriggerBox>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATriggerBox::StaticClass(), 1));
	if (Client2TriggerBox)
	{
		Client2TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnClient2TriggerBeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Client2TriggerBox is invalid"))
	}
}

void ACharacterTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ACharacterTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	
}

void ACharacterTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	
}

void ACharacterTest::CheckResult()
{
	if (bServerPassed && bClient1Passed && bClient2Passed)
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Server %s"), bServerPassed ? *FString("pass") : *FString("fail"))
		UE_LOG(LogTemp, Display, TEXT("Client 1 %s"), bClient1Passed ? *FString("pass") : *FString("fail"))
		UE_LOG(LogTemp, Display, TEXT("Client 2 %s"), bClient2Passed ? *FString("pass") : *FString("fail"))
	}
}

void ACharacterTest::InjectInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->InjectInputForAction(Action, Value, Modifiers, Triggers);
}

void ACharacterTest::StartInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action, const FVector Value)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->StartContinuousInputInjectionForAction(Action, Value, Modifiers, Triggers);
}

void ACharacterTest::StopInjectContinuousInput(UEnhancedInputLocalPlayerSubsystem* InputSubsystem, UInputAction* Action)
{
	TArray<UInputModifier*> Modifiers = {};
	TArray<UInputTrigger*> Triggers = {};

	InputSubsystem->StopContinuousInputInjectionForAction(Action);
}
