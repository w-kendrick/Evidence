// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSelectWidget.h"
#include "Components/Button.h"

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
}

void USaveSelectWidget::ConfirmButtonClicked()
{
	OnSaveSelected.ExecuteIfBound(SelectedSaveSlot);

	RemoveFromParent();
}
