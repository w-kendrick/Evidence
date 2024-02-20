// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameplayAbility.h"

bool UEIGameplayAbility::IsInputPressed() const
{
	FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec();
	return Spec && Spec->InputPressed;
}