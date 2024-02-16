// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode()
{
	
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ALobbyPlayerController* LobbyController = Cast<ALobbyPlayerController>(NewPlayer);
	if (LobbyController)
	{
		LobbyController->ClientCreateLobbyScreen();
	}

	FTimerHandle UpdateHandle;
	GetWorldTimerManager().SetTimer(UpdateHandle, this, &ALobbyGameMode::UpdatePlayerList, 1.0f, false);
}

void ALobbyGameMode::UpdatePlayerList()
{
	if (GetWorld())
	{
		TArray<AActor*> Controllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALobbyPlayerController::StaticClass(), Controllers);
		for (int i = 0; i < Controllers.Num(); i++)
		{
			ALobbyPlayerController* Controller = Cast<ALobbyPlayerController>(Controllers[i]);
			if (Controller)
			{
				Controller->ClientUpdatePlayerList();
			}
		}
	}
}