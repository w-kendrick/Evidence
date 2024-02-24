// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceOverlay.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"

void UEvidenceOverlay::ShowInteractPrompt(const float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Show overlay");
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Hide overlay");
	InteractCanvas->SetVisibility(ESlateVisibility::Hidden);
}
