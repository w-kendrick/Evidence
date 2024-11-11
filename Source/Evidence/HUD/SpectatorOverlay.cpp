// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectatorOverlay.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Player/EvidencePlayerController.h"
#include "GameFramework/PlayerState.h"

void USpectatorOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidencePlayerController* const EvidencePlayerController = Cast<AEvidencePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (EvidencePlayerController)
	{
		EvidencePlayerController->OnSpectateeChanged.AddUObject(this, &ThisClass::OnSpectateeChanged);
	}
}

void USpectatorOverlay::OnSpectateeChanged(APawn* Pawn)
{
	if (Pawn)
	{
		const APlayerState* const PlayerState = Pawn->GetPlayerState();
		if (PlayerState)
		{
			NameText->SetText(FText::FromString(PlayerState->GetPlayerName()));
		}
		else
		{
			NameText->SetText(FText::FromString(FString("")));
		}
	}
	else
	{
		NameText->SetText(FText::FromString(FString("")));
	}
}
