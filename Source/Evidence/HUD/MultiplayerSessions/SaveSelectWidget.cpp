// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSelectWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "SaveSlotWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Save/EvidenceSaveGame.h"

USaveSelectWidget::USaveSelectWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveCount = 5;
	SelectedSaveSlot = 0;
}

void USaveSelectWidget::SetSelectedIndex(const uint8 Index)
{
	SelectedSaveSlot = Index;
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
			USaveSlotWidget* const SaveSlotWidget = CreateWidget<USaveSlotWidget>(this, SaveSlotWidgetClass);
			SaveSlotWidget->OnSaveSelected.BindUObject(this, &ThisClass::OnSaveSelected);
			SaveSlotWidget->SetIndex(i);
			SlotBox->AddChildToVerticalBox(SaveSlotWidget);
			SaveSlotWidget->SetStatus(false);

			const FString SlotName = FString("Save") + FString::FromInt(i + 1);

			if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
			{
				FAsyncLoadGameFromSlotDelegate LoadedDelegate;
				LoadedDelegate.BindUObject(this, &ThisClass::OnLoadGameComplete);
				UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadedDelegate);
			}
			else
			{
				SaveSlotWidget->SetNight(1U);
				SaveSlotWidget->SetCash(0.0f);
			}
		}

		SelectSaveWidget(SelectedSaveSlot);
	}
}

void USaveSelectWidget::ConfirmButtonClicked()
{
	OnSaveConfirmed.ExecuteIfBound(SelectedSaveSlot);

	RemoveFromParent();
}

void USaveSelectWidget::OnSaveSelected(uint8 Index)
{
	SelectSaveWidget(Index);
}

void USaveSelectWidget::SelectSaveWidget(const uint8 Index)
{
	if (SlotBox)
	{
		const uint8 PrevIndex = SelectedSaveSlot;

		SelectedSaveSlot = Index;

		USaveSlotWidget* const PrevSlotWidget = Cast<USaveSlotWidget>(SlotBox->GetChildAt(PrevIndex));
		USaveSlotWidget* const NewSlotWidget = Cast<USaveSlotWidget>(SlotBox->GetChildAt(SelectedSaveSlot));

		PrevSlotWidget->SetStatus(false);
		NewSlotWidget->SetStatus(true);
	}
}

void USaveSelectWidget::OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UEvidenceSaveGame* const EvidenceSaveGame = Cast<UEvidenceSaveGame>(LoadedGameData);
	
	if (EvidenceSaveGame)
	{
		const uint8 Index = SlotMap[SlotName];

		USaveSlotWidget* const SlotWidget = Cast<USaveSlotWidget>(SlotBox->GetChildAt(Index));
		if (SlotWidget)
		{
			SlotWidget->SetNight(EvidenceSaveGame->GetNight());
			SlotWidget->SetCash(EvidenceSaveGame->GetCash());
		}
	}
}
