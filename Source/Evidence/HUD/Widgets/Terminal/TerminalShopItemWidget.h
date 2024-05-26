// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Structs/ShopItem.h"
#include "TerminalShopItemWidget.generated.h"

UCLASS()
class EVIDENCE_API UTerminalShopItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const FShopItem& NewItem);

protected:
	FShopItem Item;
	
};
