// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalShopItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/EvidenceGameState.h"
#include "Evidence/Items/Hub.h"

void UTerminalShopItemWidget::SpawnInitialize(const FShopItem& NewItem)
{
	Item = NewItem;
}

void UTerminalShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NameBlock)
	{
		NameBlock->SetText(FText::FromString(Item.Name));
	}

	if (PriceBlock)
	{
		PriceBlock->SetText(FText::FromString(FString(TEXT("$")) + FString::SanitizeFloat(Item.Price)));
	}

	if (BuyButton)
	{
		BuyButton->OnClicked.AddDynamic(this, &ThisClass::OnBuyClicked);
	}
}

void UTerminalShopItemWidget::OnBuyClicked()
{
	AEvidenceGameState* const EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (EGS)
	{
		AHub* const Hub = Cast<AHub>(EGS->GetHub());
		if (Hub)
		{
			Hub->ServerPurchaseEquipment(Item);
		}
	}
}
