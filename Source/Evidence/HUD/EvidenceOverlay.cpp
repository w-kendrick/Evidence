// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceOverlay.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ProgressBar.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"

void UEvidenceOverlay::NativeConstruct()
{
	AEvidencePlayerCharacter* PlayerChar = Cast<AEvidencePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerChar)
	{
		PlayerChar->GetInventoryComponent()->InventoryRequest.AddUObject(this, &ThisClass::OnInventoryRequest);
	}
}

void UEvidenceOverlay::ShowInteractPrompt(const float Duration)
{
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

void UEvidenceOverlay::OnInventoryRequest(bool state)
{
	InventoryWidget->SetVisibility(state ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
