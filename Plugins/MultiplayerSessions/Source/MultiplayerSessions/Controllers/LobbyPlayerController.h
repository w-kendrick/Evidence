// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyMenu;

UCLASS()
class MULTIPLAYERSESSIONS_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPlayerController();

	void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void ClientCreateLobbyScreen();

	UFUNCTION(Client, Reliable)
	void ClientUpdatePlayerList();

	UFUNCTION(Client, Reliable)
	void ClientRemoveMenu();

private:
	UPROPERTY()
	ULobbyMenu* LobbyMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULobbyMenu> LobbyClass;
	
};
