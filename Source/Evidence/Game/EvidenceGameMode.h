// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Evidence/Structs/EquipmentToID.h"
#include "Evidence/Save/EquipmentSaveData.h"
#include "EvidenceGameMode.generated.h"

class AEvidenceGameState;
class UEvidenceSaveGame;
class USaveGame;
class AEquipment;
class AWorldGenerator;

enum class EPlayerLossType : uint8
{
	Death,
	Logout
};

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

	void EndPreSetup();
	void StartNight();
	void EndNight();

	void OnPlayerDeath(APlayerController* Player);

protected:
	virtual void BeginPlay();
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
	void Logout(AController* Controller) override;
	virtual void OnMatchStateSet() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FEquipmentToID> EquipmentClassMap;

	uint8 GetEquipmentID(const AEquipment* const Equipment) const;
	TSubclassOf<AEquipment> GetEquipmentClass(const uint8 ID) const;

private:
	void SetNight(const uint32 NewNight);

	void StartPreSetup();
	void SetupWorld();
	void ResetWorld();
	void FetchWorldGenerators();

	void SaveGame();
	void SaveLocker(UEvidenceSaveGame* const SaveGame) const;
	void SaveEquipment(FEquipmentSaveData& EquipmentData, AEquipment* const Equipment) const;
	void LoadSelectedGame();
	void LoadPlayer(const APlayerController* const PlayerController);

	void TeamWipe();
	void WipeSave();

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

	uint32 Night;

	UPROPERTY()
	TArray<APlayerController*> LivingPlayers;

	UPROPERTY()
	TArray<APlayerController*> DeadPlayers;

	void AddLivingPlayer(APlayerController* Player);
	void RemoveLivingPlayer(APlayerController* Player, const EPlayerLossType LossType);
};

