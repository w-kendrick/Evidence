// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "EquipmentItem.generated.h"

class AEquipment;

/*
Equipment item for fast replication in array
*/
USTRUCT(BlueprintType)
struct FEquipmentItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FEquipmentItem()
		: FFastArraySerializerItem(), Equipment(nullptr)
	{

	}

	FEquipmentItem(AEquipment* NewEquipment)
		: FFastArraySerializerItem(), Equipment(NewEquipment)
	{

	}

	AEquipment* GetEquipment() const
	{
		return Equipment;
	}

private:
	UPROPERTY()
	AEquipment* Equipment;
};