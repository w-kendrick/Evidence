// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilitySystemComponent.h"

int32 UCharacterAbilitySystemComponent::K2_GetTagCount(FGameplayTag TagToCheck) const
{
	return GetTagCount(TagToCheck);
}
