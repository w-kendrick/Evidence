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

	bIsFocusable = true;

	if (ShopButton)
	{
		ShopButton->OnClicked.AddDynamic(this, &ThisClass::OnShopClicked);
	}

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseClicked);
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
	ShopMenu->SpawnInitialize(this);
	ShopMenu->AddToViewport();
	SetVisibility(ESlateVisibility::Hidden);
}

void UTerminalMenu::OnCloseClicked()
{
	LeaveTerminal();
}

FReply UTerminalMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "on key down");
	if (InKeyEvent.GetKey() == EscapeKey)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "escape");
		if (isActive)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "isactive");
			LeaveTerminal();
		}
	}

	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}

void UTerminalMenu::Enable()
{
	APlayerController* const PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
	}

	SetVisibility(ESlateVisibility::Visible);
	isActive = true;
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
	isActive = false;
	
	if (ShopMenu)
	{
		ShopMenu->RemoveFromParent();
		ShopMenu = nullptr;
	}
}
