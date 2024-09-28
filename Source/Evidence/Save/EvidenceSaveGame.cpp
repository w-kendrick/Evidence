// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceSaveGame.h"

void UEvidenceSaveGame::SetNight(const int32& NewNight)
{
	Night = NewNight;
}

void UEvidenceSaveGame::SetCash(const double& NewCash)
{
	Cash = NewCash;
}

void UEvidenceSaveGame::AddPlayerSave(const FPlayerSave& Save)
{
	PlayerSaves.Add(Save);
}
