// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlotWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USaveSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &ThisClass::SelectButtonClicked);
	}
}

void USaveSlotWidget::SelectButtonClicked()
{
}

void USaveSlotWidget::SetName(const FString& Name)
{
	SlotName = Name;
	SlotNameText->SetText(FText::FromString(SlotName));
}