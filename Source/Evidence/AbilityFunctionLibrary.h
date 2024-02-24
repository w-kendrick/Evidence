// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h" 
#include "AbilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UAbilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|TargetData")
	static void ClearTargetData(UPARAM(ref) FGameplayAbilityTargetDataHandle& TargetData);
	
};
