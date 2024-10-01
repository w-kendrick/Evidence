// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerSessions/Widgets/Lobby/LobbyMenu.h"
#include "EvidenceLobbyMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceLobbyMenu : public ULobbyMenu
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;

	UFUNCTION()
	void LoadButtonClicked();
	
};
