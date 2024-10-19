// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SpectateeItem.h"
#include "Evidence/Character/BaseCharacter.h"
#include "SpectateeList.generated.h"

/*
Manages list of spectatees
*/
USTRUCT(BlueprintType)
struct FSpectateeList : public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FSpectateeList()
	{
		
	}

	FSpectateeItem& operator[](int Index)
	{
		return Entries[Index];
	}

	const FSpectateeItem& operator[](int Index) const
	{
		return Entries[Index];
	}

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FSpectateeItem, FSpectateeList>(Entries, DeltaParms, *this);
	}

	void AddEntry(APawn* const Spectatee)
	{
		Entries.Add(FSpectateeItem(Spectatee));
	}

	void RemoveEntry(APawn* const Spectatee)
	{
		UE_LOG(LogTemp, Warning, TEXT("Remove entry"));
		for (FSpectateeItem& Entry : Entries)
		{
			if (Entry.GetSpectatee() == Spectatee)
			{
				Entries.Remove(Entry);
				break;
			}
		}
	}

private:
	UPROPERTY()
	TArray<FSpectateeItem> Entries;
};