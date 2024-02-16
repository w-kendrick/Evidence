// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenu.generated.h"

class ULobbyPlayerRow;
class UHostMenu;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API ULobbyMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Refresh();

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* FriendBox;

	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void RefreshButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULobbyPlayerRow> PlayerRowClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHostMenu> HostMenuClass;

	UPROPERTY(EditDefaultsOnly)
	FString StartMapAddress = FString("Game/Maps/GameStartMap");

	// Subsystem for handling online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	void LoadMap();
};
