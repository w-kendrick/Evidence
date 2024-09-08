// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceOverlay.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Widgets/Terminal/TerminalMenu.h"
#include "Widgets/AttachmentBench/AttachmentBenchWidget.h"
#include "Evidence/EvidencePlayerController.h"
#include "Evidence/Character/BaseCharacter.h"

void UEvidenceOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (EPC)
	{
		EPC->OnSetTerminalMenuVisibility.BindUObject(this, &ThisClass::SetTerminalMenuVisibility);
		EPC->OnSetAttachmentWidgetVisibility.BindUObject(this, &ThisClass::SetAttachmentVisibility);
		EPC->OnSetInteractWidgetVisibility.BindUObject(this, &ThisClass::SetInteractPromptVisibility);
	}

	TerminalMenu->SetVisibility(ESlateVisibility::Hidden);
	AttachmentWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UEvidenceOverlay::ShowInteractPrompt(const float Duration, const FString DisplayString)
{
	InteractText->SetText(FText::FromString(DisplayString));

	if (Duration > 0)
	{
		InteractSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		InteractSwitcher->SetActiveWidgetIndex(0);
	}

	InteractCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UEvidenceOverlay::HideInteractPrompt()
{
	InteractCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UEvidenceOverlay::StartInteractionTimer(const float Duration)
{
	if (Duration > 0)
	{
		InteractBar->SetPercent(0.0f);
		CurrentInteractionTime = 0.0f;
		InteractionDuration = Duration;
		GetWorld()->GetTimerManager().SetTimer(InteractionTimer, this, &ThisClass::InteractionProgressTick, InteractionTick, true, InteractionTick);
	}
}

void UEvidenceOverlay::StopInteractionTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimer);
	InteractBar->SetPercent(0.0f);
}

void UEvidenceOverlay::InteractionProgressTick()
{
	CurrentInteractionTime += InteractionTick;
	InteractBar->SetPercent(CurrentInteractionTime / InteractionDuration);
}

void UEvidenceOverlay::SetInteractPromptVisibility(bool bVisibility, float Duration, FString DisplayString)
{
	if (bVisibility)
	{
		ShowInteractPrompt(Duration, DisplayString);
	}
	else
	{
		HideInteractPrompt();
	}
}

void UEvidenceOverlay::SetTerminalMenuVisibility(bool bVisibility)
{
	if (bVisibility)
	{
		TerminalMenu->Enable();
	}
	else
	{
		TerminalMenu->Disable();
	}
}

void UEvidenceOverlay::SetAttachmentVisibility(bool bVisibility)
{
	AttachmentWidget->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (bVisibility)
	{
		AttachmentWidget->Enable();
	}
	else
	{
		AttachmentWidget->Disable();
	}
}