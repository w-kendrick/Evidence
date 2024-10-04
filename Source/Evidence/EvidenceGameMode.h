// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EvidenceGameMode.generated.h"

class AEvidenceGameState;
class UEvidenceSaveGame;
class USaveGame;

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

private:
	void LoadSelectedGame();
	void LoadPlayer(const FUniqueNetIdRepl& ID);

	void OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	UPROPERTY()
	TObjectPtr<AEvidenceGameState> EvidenceGameState;

	UPROPERTY()
	UEvidenceSaveGame* EvidenceSaveGame;

	UPROPERTY()
	TArray<FUniqueNetIdRepl> PendingPlayerLoads;

	FTimerHandle SaveHandle;
};

