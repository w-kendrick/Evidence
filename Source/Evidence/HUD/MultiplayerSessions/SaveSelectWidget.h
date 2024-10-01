// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSelectWidget.generated.h"

class UButton;
class UVerticalBox;
class USaveSlotWidget;

DECLARE_DELEGATE_OneParam(FOnSaveSelected, FString)

/**
 * 
 */
UCLASS()
class EVIDENCE_API USaveSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USaveSelectWidget(const FObjectInitializer& ObjectInitializer);

	FOnSaveSelected OnSaveSelected;

protected:
	virtual void NativeConstruct() override;

	FString SelectedSaveSlot;

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
	
};
