// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AdvancedGameplayAbility.h"
#include "AbilitySystemComponent.h"

void UAdvancedGameplayAbility::CancelAbilityWithTags(const FGameplayTagContainer Tags)
{
	GetAbilitySystemComponentFromActorInfo_Ensured()->CancelAbilities(&Tags);
}