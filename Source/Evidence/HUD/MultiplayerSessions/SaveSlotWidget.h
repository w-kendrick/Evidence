// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlotWidget.generated.h"

class UButton;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FOnSaveSelected, uint8)

/**
 * 
 */
UCLASS()
class EVIDENCE_API USaveSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetStatus(const bool bStatus);
	void SetIndex(const uint8 Index);
	void SetNight(const uint32 Night);
	void SetCash(const float Cash);

	FOnSaveSelected OnSaveSelected;

protected:
	virtual void NativeConstruct() override;

	uint8 SlotIndex;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNightText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotCashText;

	UPROPERTY(meta = (BindWidget))
	class UImage* SelectedBorder;

	UFUNCTION()
	void SelectButtonClicked();
	
};
