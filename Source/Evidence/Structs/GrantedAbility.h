// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GrantedAbility.generated.h"

class UEIGameplayAbility;

USTRUCT()
struct FGrantedAbility
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UEIGameplayAbility> AbilityClass;

	FGameplayAbilitySpecHandle AbilityHandle;

	FGrantedAbility(const TSubclassOf<UEIGameplayAbility>& NewClass, const FGameplayAbilitySpecHandle& NewHandle)
		: AbilityClass(NewClass), AbilityHandle(NewHandle)
	{

	}

	FGrantedAbility(const FGrantedAbility& GA)
		: AbilityClass(GA.AbilityClass), AbilityHandle(GA.AbilityHandle)
	{

	}

	FGrantedAbility()
		: AbilityClass(nullptr), AbilityHandle(FGameplayAbilitySpecHandle())
	{

	}
};