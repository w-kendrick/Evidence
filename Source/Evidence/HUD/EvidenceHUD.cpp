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

UEvidenceOverlay* AEvidenceHUD::GetOverlay() const
{
	return Overlay;
}
