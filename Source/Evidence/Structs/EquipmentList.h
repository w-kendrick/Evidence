// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "EquipmentItem.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Character/BaseCharacter.h"
#include "EquipmentList.generated.h"

/*
Manages list of equipment items
*/
USTRUCT(BlueprintType)
struct FEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FEquipmentList()
		: FEquipmentList(0U)
	{

	}

	FEquipmentList(const uint8 SIZE)
	{
		Entries.SetNum(SIZE);
	}

	FEquipmentItem& operator[](int Index)
	{
		return Entries[Index];
	}

	const FEquipmentItem& operator[](int Index) const
	{
		return Entries[Index];
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
		return FFastArraySerializer::FastArrayDeltaSerialize<FEquipmentItem, FEquipmentList>(Entries, DeltaParms, *this);
	}

	void AddEntry(AEquipment* const Equipment, const uint8 Index)
	{
		RemoveEntry(Index);
		Entries[Index] = FEquipmentItem(Equipment);
	}

	void RemoveEntry(const uint8 Index)
	{
		AEquipment* const PrevEquipment = Entries[Index].GetEquipment();

		if (PrevEquipment)
		{
			PrevEquipment->Drop();
		}
		Entries[Index] = FEquipmentItem(nullptr);
	}

private:
	UPROPERTY()
	TArray<FEquipmentItem> Entries;
};