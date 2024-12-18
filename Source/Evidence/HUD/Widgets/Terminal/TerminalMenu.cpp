// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalMenu.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Hub/Hub.h"
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
	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	if (Hub)
	{
		Hub->Relinquish();
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
