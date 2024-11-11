// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceHUD.h"
#include "EvidenceOverlay.h"
#include "SpectatorOverlay.h"
#include "Evidence/Player/EvidencePlayerController.h"
#include "Evidence/Delegates.h"

void AEvidenceHUD::BeginPlay()
{
	Super::BeginPlay();
	AddEvidenceOverlay();
	AddSpectatorOverlay();

	OnSpectatingChanged(false);

	AEvidencePlayerController* const EvidencePlayerController = Cast<AEvidencePlayerController>(GetOwningPlayerController());
	if (EvidencePlayerController)
	{
		EvidencePlayerController->OnSpectatingChanged.AddUObject(this, &ThisClass::OnSpectatingChanged);
	}
}

void AEvidenceHUD::AddEvidenceOverlay()
{
	if (Overlay)
	{
		return;
	}

	Overlay = CreateWidget<UEvidenceOverlay>(GetOwningPlayerController(), EvidenceOverlayClass);
	if (Overlay)
	{
		Overlay->AddToViewport();
	}
}

void AEvidenceHUD::AddSpectatorOverlay()
{
	if (SpectatorOverlay)
	{
		return;
	}

	SpectatorOverlay = CreateWidget<USpectatorOverlay>(GetOwningPlayerController(), SpectatorOverlayClass);
	if (SpectatorOverlay)
	{
		SpectatorOverlay->AddToViewport();
	}
}

void AEvidenceHUD::OnSpectatingChanged(bool bIsSpectating)
{
	if (bIsSpectating)
	{
		Overlay->SetVisibility(ESlateVisibility::Hidden);
		SpectatorOverlay->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Overlay->SetVisibility(ESlateVisibility::Visible);
		SpectatorOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}
