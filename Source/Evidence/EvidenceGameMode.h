// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EvidenceGameMode.generated.h"

class AEvidenceGameState;

UCLASS(minimalapi)
class AEvidenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEvidenceGameMode();
	virtual void InitGameState() override;

	void SaveGame();

protected:
	virtual void BeginPlay();

private:
	void LoadSelectedGame();

	void OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UPROPERTY()
	TObjectPtr<AEvidenceGameState> EvidenceGameState;
};

