// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceOverlay.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ProgressBar.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "Widgets/Terminal/TerminalMenu.h"
#include "Widgets/AttachmentBench/AttachmentBenchWidget.h"
#include "Evidence/EvidencePlayerController.h"

void UEvidenceOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	const AEvidencePlayerCharacter* const PlayerChar = Cast<AEvidencePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerChar)
	{
		PlayerChar->GetInventoryComponent()->InventoryRequest.AddUObject(this, &ThisClass::OnInventoryRequest);

		InventoryWidget->SetInventoryComp(PlayerChar->GetInventoryComponent());
	}

	AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (EPC)
	{
		EPC->OnSetAttachmentWidgetVisibility.BindUObject(this, &ThisClass::SetAttachmentVisibility);
	}

	TerminalMenu->SetVisibility(ESlateVisibility::Hidden);
	AttachmentWidget->SetVisibility(ESlateVisibility::Hidden);
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

void UEvidenceOverlay::OnInventoryRequest()
{
	bInventoryWidgetVisible = !bInventoryWidgetVisible;

	InventoryWidget->SetVisibility(bInventoryWidgetVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (bInventoryWidgetVisible)
	{
		APlayerController* const PC = GetOwningPlayer();
		if (PC)
		{
			PC->SetInputMode(FInputModeGameAndUI());
			PC->bShowMouseCursor = true;
		}
		InventoryWidget->Update();
	}
	else
	{
		APlayerController* const PC = GetOwningPlayer();
		if (PC)
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->bShowMouseCursor = false;
		}
	}
}

void UEvidenceOverlay::SetAttachmentVisibility(bool bVisibility)
{
	AttachmentWidget->SetVisibility(bVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UEvidenceOverlay::ShowTerminalMenu()
{
	TerminalMenu->Enable();
}

void UEvidenceOverlay::HideTerminalMenu()
{
	TerminalMenu->Disable();
}