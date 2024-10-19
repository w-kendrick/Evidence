// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "SpectateeItem.h"
#include "Evidence/Character/BaseCharacter.h"
#include "SpectateeList.generated.h"

/*
Manages list of spectators
*/
USTRUCT(BlueprintType)
struct FSpectateeList : public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FSpectateeList()
	{
		
	}

	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
	{

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

	void AddEntry(ABaseCharacter* const Spectatee)
	{
		Entries.Add(FSpectateeItem(Spectatee));
	}

	void RemoveEntry(ABaseCharacter* const Spectatee)
	{
		for (FSpectateeItem& Entry : Entries)
		{
			if (Entry.GetSpectatee() == Spectatee)
			{

			}
		}
	}

private:
	UPROPERTY()
	TArray<FSpectateeItem> Entries;
};