// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "GetTagCount", ScriptName = "GetTagCount"))
	int32 K2_GetTagCount(FGameplayTag& TagToCheck) const;

	virtual void AbilityLocalInputPressed(int32 InputID) override;
	
};
