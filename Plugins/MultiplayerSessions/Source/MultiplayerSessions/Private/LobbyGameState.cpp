// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyPlayerController.h"

ALobbyGameState::ALobbyGameState()
{

}

void ALobbyGameState::ServerRemoveMenu_Implementation()
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALobbyPlayerController::StaticClass(), Controllers);
	for (int i = 0; i < Controllers.Num(); i++)
	{
		ALobbyPlayerController* LobbyController = Cast<ALobbyPlayerController>(Controllers[i]);
		if (LobbyController)
		{

		}
	}
}