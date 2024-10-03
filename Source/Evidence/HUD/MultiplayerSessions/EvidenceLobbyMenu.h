// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerSessions/Widgets/Lobby/LobbyMenu.h"
#include "EvidenceLobbyMenu.generated.h"

class UButton;
class USaveSelectWidget;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceLobbyMenu : public ULobbyMenu
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveSelectWidget> SaveSelectWidgetClass;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectSaveButton;

	UFUNCTION()
	void SelectSaveButtonClicked();

	void OnSaveConfirmed(uint8 SaveSlot);
	
};
