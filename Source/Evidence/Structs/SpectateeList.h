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
		int32 FoundIndex = -1;
		for (int32 Index = 0; Index < Entries.Num(); Index++)
		{
			const FSpectateeItem& Entry = Entries[Index];

			if (Entry.GetSpectatee() == Spectatee)
			{
				FoundIndex = Index;
			}
		}

		if (FoundIndex != -1)
		{
			Entries.RemoveAt(FoundIndex);
		}
	}

	int32 GetNum() const
	{
		return Entries.Num();
	}

private:
	UPROPERTY()
	TArray<FSpectateeItem> Entries;
};