// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SpectateeItem.generated.h"

class APawn;

/*
Spectatee item for fast replication in array
*/
USTRUCT(BlueprintType)
struct FSpectateeItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FSpectateeItem()
		: FFastArraySerializerItem(), Spectatee(nullptr)
	{

	}

	FSpectateeItem(APawn* NewSpectatee)
		: FFastArraySerializerItem(), Spectatee(NewSpectatee)
	{

	}

	bool operator==(const FSpectateeItem& rhs)
	{
		return Spectatee == rhs.GetSpectatee();
	}

	APawn* GetSpectatee() const
	{
		return Spectatee;
	}

private:
	UPROPERTY()
	APawn* Spectatee;
};