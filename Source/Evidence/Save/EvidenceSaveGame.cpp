// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceSaveGame.h"
#include "Evidence/Evidence.h"

UEvidenceSaveGame::UEvidenceSaveGame()
{
	Night = DEFAULT_STARTING_NIGHT;
	Cash = DEFAULT_STARTING_CASH;
}

void UEvidenceSaveGame::SetNight(const uint32& NewNight)
{
	Night = NewNight;
}

void UEvidenceSaveGame::SetCash(const double& NewCash)
{
	Cash = NewCash;
}

void UEvidenceSaveGame::AddPlayerSave(const FUniqueNetIdRepl ID, const FPlayerSave Save)
{
	PlayerSaves.Add(ID, Save);
}

bool UEvidenceSaveGame::GetPlayerSave(const FUniqueNetIdRepl& ID, FPlayerSave& Save)
{
	bool bFound = false;

	if (PlayerSaves.Contains(ID))
	{
		bFound = true;
		Save = PlayerSaves[ID];
	}

	return bFound;
}
