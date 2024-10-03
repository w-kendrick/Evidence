// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlotWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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
	OnSaveSelected.ExecuteIfBound(SlotIndex);
}

void USaveSlotWidget::SetStatus(const bool bStatus)
{
	SelectedBorder->SetVisibility(bStatus ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USaveSlotWidget::SetIndex(const uint8 Index)
{
	SlotIndex = Index;
	SlotNameText->SetText(FText::FromString(FString("Save") + FString::FromInt(Index + 1)));
}