// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShopItem.generated.h"

class AEquipment;

USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Price;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> Item;
};