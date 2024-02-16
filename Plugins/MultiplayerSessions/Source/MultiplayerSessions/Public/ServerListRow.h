// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ServerListRow.generated.h"

class UServerBrowser;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UServerListRow : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(FOnlineSessionSearchResult Result, UServerBrowser* Browser);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MatchText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PingText;

	UFUNCTION()
	void JoinButtonClicked();

	FOnlineSessionSearchResult SearchResult;

	// Subsystem for handling online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	UServerBrowser* OwningBrowser;

	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	
};
