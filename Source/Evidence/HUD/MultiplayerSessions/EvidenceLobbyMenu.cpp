// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceLobbyMenu.h"
#include "Components/Button.h"
#include "SaveSelectWidget.h"
#include "Evidence/Game/EvidenceGameInstance.h"

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
	SaveSelectWidget->SetSelectedIndex(SelectedSlot);
	SaveSelectWidget->AddToViewport();
}

void UEvidenceLobbyMenu::OnSaveConfirmed(uint8 SaveSlot)
{
	SelectedSlot = SaveSlot;
	const FString& SelectedSlotName = FString("Save") + FString::FromInt(SaveSlot + 1);

	UEvidenceGameInstance* const EvidenceGameInstance = GetGameInstance<UEvidenceGameInstance>();
	if (EvidenceGameInstance)
	{
		EvidenceGameInstance->SetSlotName(SelectedSlotName);
	}
}
