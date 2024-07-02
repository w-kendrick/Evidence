// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EIGameplayAbility.h"
#include "EIEquipFromInventory.generated.h"

UCLASS()
class EVIDENCE_API UEIEquipFromInventory : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UEIEquipFromInventory();

	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
	
};
