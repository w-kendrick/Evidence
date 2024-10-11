// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalShopMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
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

	AEvidenceGameState* const EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EGS)
	{
		AHub* const Hub = Cast<AHub>(EGS->GetHub());
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
