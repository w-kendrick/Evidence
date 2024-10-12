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

namespace MatchState
{
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

	FTimerHandle SaveHandle;
	FTimerHandle SetupHandle;
	FTimerHandle NightHandle;

	UPROPERTY(EditDefaultsOnly)
	FTransform DefaultTransform;

	UPROPERTY(EditDefaultsOnly)
	float MaxSetupTime;

	UPROPERTY(EditDefaultsOnly)
	float MaxNightTime;
};
