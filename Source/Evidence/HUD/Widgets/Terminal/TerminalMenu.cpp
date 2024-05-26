// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Components/Button.h"
#include "TerminalShopMenu.h"

void UTerminalMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ShopButton)
	{
		ShopButton->OnClicked.AddDynamic(this, &ThisClass::OnShopClicked);
	}
}

void UTerminalMenu::LeaveTerminal()
{
	AEvidenceGameState* const EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EGS)
	{
		AHub* const Hub = EGS->GetHub();
		if (Hub)
		{
			Disable();
			Hub->RelinquishTerminal();
		}
	}
}

void UTerminalMenu::OnShopClicked()
{
	ShopMenu = CreateWidget<UTerminalShopMenu>(this, ShopMenuClass);
	ShopMenu->AddToViewport();
	SetVisibility(ESlateVisibility::Hidden);
}

void UTerminalMenu::Enable()
{
	APlayerController* const PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}

	SetVisibility(ESlateVisibility::Visible);
	//GetWorld()->GetTimerManager().SetTimer(LeaveHandle, this, &ThisClass::LeaveTerminal, 5.0f, false);
}

void UTerminalMenu::Disable()
{
	APlayerController* const PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	SetVisibility(ESlateVisibility::Hidden);
	
	if (ShopMenu)
	{
		ShopMenu->RemoveFromParent();
		ShopMenu = nullptr;
	}
}
