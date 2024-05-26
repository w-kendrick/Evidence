// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalShopMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/EvidenceGameState.h"
#include "Evidence/Items/Hub.h"
#include "TerminalShopItemWidget.h"

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
				}
			}
		}
	}
}
