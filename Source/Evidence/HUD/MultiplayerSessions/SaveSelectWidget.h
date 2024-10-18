// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSelectWidget.generated.h"

class UButton;
class UVerticalBox;
class USaveSlotWidget;
class USaveGame;

DECLARE_DELEGATE_OneParam(FOnSaveConfirmed, uint8)

/**
 * 
 */
UCLASS()
class EVIDENCE_API USaveSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USaveSelectWidget(const FObjectInitializer& ObjectInitializer);
	void SetSelectedIndex(const uint8 Index);

	FOnSaveConfirmed OnSaveConfirmed;

protected:
	virtual void NativeConstruct() override;

	uint8 SelectedSaveSlot;

	UPROPERTY(EditDefaultsOnly)
	uint8 SaveCount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveSlotWidget> SaveSlotWidgetClass;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* SlotBox;

	UFUNCTION()
	void ConfirmButtonClicked();

	void OnSaveSelected(uint8 Index);

	void SelectSaveWidget(const uint8 Index);

	void OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	TMap<FString, uint8> SlotMap =
	{ 
		{ FString("Save1"), 0U },
		{ FString("Save2"), 1U },
		{ FString("Save3"), 2U },
		{ FString("Save4"), 3U },
		{ FString("Save5"), 4U }
	};
	
};
