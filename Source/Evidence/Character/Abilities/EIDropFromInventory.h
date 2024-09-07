// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "EIDropFromInventory.generated.h"

UCLASS()
class EVIDENCE_API UEIDropFromInventory : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UEIDropFromInventory();

	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
	
};
