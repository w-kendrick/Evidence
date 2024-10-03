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
	SaveSelectWidget->OnSaveConfirmed.BindUObject(this, &ThisClass::OnSaveConfirmed);
	SaveSelectWidget->AddToViewport();
}

void UEvidenceLobbyMenu::OnSaveConfirmed(uint8 SaveSlot)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString("Confirmed ") + FString::FromInt(SaveSlot));
}
