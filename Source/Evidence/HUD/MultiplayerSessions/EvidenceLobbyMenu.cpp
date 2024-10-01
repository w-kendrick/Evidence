// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceLobbyMenu.h"
#include "Components/Button.h"
#include "SaveSelectWidget.h"

void UEvidenceLobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectSaveButton)
	{
		SelectSaveButton->OnClicked.AddDynamic(this, &ThisClass::SelectSaveButtonClicked);
	}
}

void UEvidenceLobbyMenu::SelectSaveButtonClicked()
{
	USaveSelectWidget* const SaveSelectWidget = CreateWidget<USaveSelectWidget>(this, SaveSelectWidgetClass);
	SaveSelectWidget->OnSaveSelected.BindUObject(this, &ThisClass::OnSaveSelected);
	SaveSelectWidget->AddToViewport();
}

void UEvidenceLobbyMenu::OnSaveSelected(FString SaveSlot)
{
}
