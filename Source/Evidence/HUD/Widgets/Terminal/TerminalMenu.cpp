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

void UTerminalMenu::LeaveEvent()
{
	AEvidenceGameState* const EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EGS)
	{
		AHub* const Hub = EGS->GetHub();
		if (Hub)
		{
			Hub->RelinquishTerminal();
		}
	}

	Super::LeaveEvent();
}

void UTerminalMenu::OnShopClicked()
{
	ShopMenu = CreateWidget<UTerminalShopMenu>(this, ShopMenuClass);
	ShopMenu->SpawnInitialize(this);
	ShopMenu->AddToViewport();
	SetVisibility(ESlateVisibility::Hidden);
}

void UTerminalMenu::Disable()
{
	Super::Disable();
	
	if (ShopMenu)
	{
		ShopMenu->RemoveFromParent();
		ShopMenu = nullptr;
	}
}
