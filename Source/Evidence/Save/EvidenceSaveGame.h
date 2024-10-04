// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSave.h"
#include "EvidenceSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	void SetNight(const uint32& NewNight);
	void SetCash(const double& NewCash);
	void AddPlayerSave(const FUniqueNetIdRepl ID, const FPlayerSave Save);

private:
	uint32 Night;
	float Cash;

	UPROPERTY()
	TMap<FUniqueNetIdRepl, FPlayerSave> PlayerSaves;
};
