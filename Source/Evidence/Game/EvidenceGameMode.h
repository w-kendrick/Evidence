// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Evidence/Structs/EquipmentToID.h"
#include "EvidenceGameMode.generated.h"

class AEvidenceGameState;
class UEvidenceSaveGame;
class USaveGame;
class AEquipment;
class AWorldGenerator;

namespace MatchState
{
	const FName PreSetup = FName("PreSetup"); //Pre-Setup period (only exited by player input)
	const FName Setup = FName("Setup"); //Setup period
	const FName Night = FName("Night"); //Night is ongoing with enemies active and evidence available
	const FName PostNight = FName("PostNight"); //After the night has ended
}

UCLASS(minimalapi)
class AEvidenceGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEvidenceGameMode();
	virtual void InitGameState() override;

	void SaveGame();
	void EndPreSetup();

protected:
	virtual void BeginPlay();
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
	virtual void OnMatchStateSet() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FEquipmentToID> EquipmentClassMap;

	uint8 GetEquipmentID(const AEquipment* const Equipment) const;
	TSubclassOf<AEquipment> GetEquipmentClass(const uint8 ID) const;

private:
	void StartNight();
	void EndNight();
	void StartPreSetup();
	void SetupWorld();
	void ResetWorld();
	void FetchWorldGenerators();

	void LoadSelectedGame();
	void LoadPlayer(const APlayerController* const PlayerController);

	void OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	UPROPERTY()
	TObjectPtr<AEvidenceGameState> EvidenceGameState;

	UPROPERTY()
	UEvidenceSaveGame* EvidenceSaveGame;

	UPROPERTY()
	TArray<APlayerController*> PendingPlayerLoads;

	FTimerHandle SetupHandle;
	FTimerHandle NightHandle;
	FTimerHandle PostNightHandle;

	UPROPERTY(EditDefaultsOnly)
	FTransform DefaultTransform;

	UPROPERTY(EditDefaultsOnly)
	float MaxSetupTime;

	UPROPERTY(EditDefaultsOnly)
	float MaxNightTime;

	UPROPERTY(EditDefaultsOnly)
	float PostNightTime;

	UPROPERTY()
	TArray<AWorldGenerator*> WorldGenerators;

	uint16 Night;
};

