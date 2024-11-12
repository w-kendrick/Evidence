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
	UEvidenceSaveGame();

	void SetNight(const uint32& NewNight);
	void SetCash(const double& NewCash);
	void AddPlayerSave(const FUniqueNetIdRepl ID, const FPlayerSave Save);
	bool GetPlayerSave(const FUniqueNetIdRepl& ID, FPlayerSave& Save);
	void AddLockerEquipment(const FEquipmentSaveData Save);

	uint32 GetNight() const { return Night; }
	float GetCash() const { return Cash; }

private:
	UPROPERTY()
	uint32 Night;

	UPROPERTY()
	float Cash;

	UPROPERTY()
	TMap<FUniqueNetIdRepl, FPlayerSave> PlayerSaves;

	UPROPERTY()
	TArray<FEquipmentSaveData> LockerEquipment;
};
