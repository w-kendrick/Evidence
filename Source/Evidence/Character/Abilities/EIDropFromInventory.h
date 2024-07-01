// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EIGameplayAbility.h"
#include "EIDropFromInventory.generated.h"

UCLASS()
class EVIDENCE_API UEIDropFromInventory : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UEIDropFromInventory();

	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
	
};
