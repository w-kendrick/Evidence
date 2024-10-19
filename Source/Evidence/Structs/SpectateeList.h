// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SpectateeItem.h"
#include "Evidence/Character/BaseCharacter.h"
#include "SpectateeList.generated.h"

DECLARE_DELEGATE_OneParam(FOnEntryRemoved, int32)

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

	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
	{
		for (const int32 Index : RemovedIndices)
		{
			OnEntryRemoved.ExecuteIfBound(Index);
		}
	}

	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
	{

	}

	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
	{

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
		for (FSpectateeItem& Entry : Entries)
		{
			if (Entry.GetSpectatee() == Spectatee)
			{
				Entries.Remove(Entry);
				break;
			}
		}
	}

	FOnEntryRemoved OnEntryRemoved;

private:
	UPROPERTY()
	TArray<FSpectateeItem> Entries;
};