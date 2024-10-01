// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlotWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class EVIDENCE_API USaveSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetName(const FString& Name);

protected:
	virtual void NativeConstruct() override;

	FString SlotName;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNameText;

	UFUNCTION()
	void SelectButtonClicked();
	
};
