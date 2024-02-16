// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HostMenu.generated.h"

class UMenu;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UHostMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class USlider* PlayerSlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountText;

	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void PlayerSliderChanged(float Value);

	int MaxPlayerCount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMenu> MenuClass;

	UPROPERTY(EditDefaultsOnly)
	FString LobbyMapAddress;

	// Subsystem for handling online session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
};
