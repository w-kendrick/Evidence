// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalShopMenu.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Hub/Hub.h"
#include "TerminalShopItemWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "TerminalMenu.h"

void UTerminalShopMenu::SpawnInitialize(UTerminalMenu* Menu)
{
	TerminalMenu = Menu;
}

void UTerminalShopMenu::NativeConstruct()
{
	Super::NativeConstruct();

	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	if (Hub)
	{
		const TArray<FShopItem>& Items = Hub->GetShopItems();

		for (const FShopItem& Item : Items)
		{
			UTerminalShopItemWidget* const ItemWidget = CreateWidget<UTerminalShopItemWidget>(this, ItemWidgetClass);
			if (ItemWidget)
			{
				ItemWidget->SpawnInitialize(Item);
				Box->AddChild(ItemWidget);
			}
		}
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &ThisClass::OnBackClicked);
	}
}

void UTerminalShopMenu::OnBackClicked()
{
	TerminalMenu->Enable();
	RemoveFromParent();
}
