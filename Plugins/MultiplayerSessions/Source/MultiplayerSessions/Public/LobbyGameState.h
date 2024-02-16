// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()

public:
	ALobbyGameState();

	UFUNCTION(Server, Reliable)
	void ServerRemoveMenu();

};
