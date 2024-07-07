// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceHUD.h"
#include "EvidenceOverlay.h"
#include "GameFramework/PlayerController.h"

void AEvidenceHUD::BeginPlay()
{
	Super::BeginPlay();
	AddOverlay();
}

void AEvidenceHUD::AddOverlay()
{
	if (Overlay)
	{
		return;
	}

	Overlay = CreateWidget<UEvidenceOverlay>(GetOwningPlayerController(), OverlayClass);
	if (Overlay)
	{
		Overlay->AddToViewport();
	}
}

void AEvidenceHUD::StartInteractionTimer(const float Duration)
{
	if (Overlay)
	{
		Overlay->StartInteractionTimer(Duration);
	}
}

void AEvidenceHUD::StopInteractionTimer()
{
	if (Overlay)
	{
		Overlay->StopInteractionTimer();
	}
}

UEvidenceOverlay* AEvidenceHUD::GetOverlay() const
{
	return Overlay;
}
