// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceOverlay.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Widgets/Terminal/TerminalMenu.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Evidence/Player/EvidencePlayerController.h"
#include "Evidence/Character/BaseCharacter.h"

void UEvidenceOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (EPC)
	{
		EPC->OnSetTerminalMenuVisibility.BindUObject(this, &ThisClass::SetTerminalMenuVisibility);
		EPC->OnSetInteractWidgetVisibility.BindUObject(this, &ThisClass::SetInteractPromptVisibility);
		EPC->OnInteractTimerStateChanged.BindUObject(this, &ThisClass::SetInteractTimerState);
	}

	AEvidenceGameState* const EvidenceGameState = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EvidenceGameState)
	{
		EvidenceGameState->OnNightChanged.AddUObject(this, &ThisClass::OnNightChanged);
	}

	TerminalMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UEvidenceOverlay::ShowInteractPrompt(const float Duration, const FString DisplayString)
{
	InstantInteractText->SetText(FText::FromString(DisplayString));
	DurationInteractText->SetText(FText::FromString(DisplayString));

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

void UEvidenceOverlay::SetInteractTimerState(bool bState, float Duration)
{
	if (bState)
	{
		StartInteractionTimer(Duration);
	}
	else
	{
		StopInteractionTimer();
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

void UEvidenceOverlay::OnNightChanged(uint32 Night)
{
	NightText->SetText(FText::FromString(FString::FromInt(Night)));
}