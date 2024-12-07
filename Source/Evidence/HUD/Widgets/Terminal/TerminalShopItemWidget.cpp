// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalShopItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Evidence/Hub/Hub.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"

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
	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	if (Hub)
	{
		Hub->ServerPurchaseEquipment(Item);
	}
}
