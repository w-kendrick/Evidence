// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSwapAbility.h"

void ULockerSwapAbility::Activate(const FGameplayEventData& EventData)
{
	FGameplayAbilityTargetData* const Data = EventData.TargetData.Data[0].Get();

	const uint8 InventoryIndex = Data->GetHitResult()->FaceIndex;
	const uint8 LockerIndex = Data->GetHitResult()->ElementIndex;
}
