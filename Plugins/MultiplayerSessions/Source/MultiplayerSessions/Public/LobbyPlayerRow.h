// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerRow.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API ULobbyPlayerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(APlayerState* Ref);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* KickButton;

	UFUNCTION()
	void KickButtonClicked();

	APlayerState* PlayerStateRef;
	
};
