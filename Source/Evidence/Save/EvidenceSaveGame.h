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
	void SetNight(const int32& NewNight);
	void SetCash(const double& NewCash);
	void AddPlayerSave(const FPlayerSave& Save);

private:
	int32 Night;
	double Cash;

	UPROPERTY()
	TArray<FPlayerSave> PlayerSaves;
};
