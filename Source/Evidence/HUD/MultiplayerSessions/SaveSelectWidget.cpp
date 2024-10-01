// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSelectWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "SaveSlotWidget.h"

USaveSelectWidget::USaveSelectWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveCount = 5;
	SelectedSaveSlot = FString("Save1");
}

void USaveSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &ThisClass::ConfirmButtonClicked);
	}

	if (SlotBox)
	{
		for (uint8 i = 0; i < SaveCount; i++)
		{
			const FString SlotName = FString("Save") + FString::FromInt(i + 1);

			USaveSlotWidget* const SaveSlotWidget = CreateWidget<USaveSlotWidget>(this, SaveSlotWidgetClass);
			SaveSlotWidget->SetName(SlotName);
			SlotBox->AddChildToVerticalBox(SaveSlotWidget);
		}
	}
}

void USaveSelectWidget::ConfirmButtonClicked()
{
	OnSaveSelected.ExecuteIfBound(SelectedSaveSlot);

	RemoveFromParent();
}
