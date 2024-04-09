// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadGunAbility.h"

UReloadGunAbility::UReloadGunAbility()
{
	AbilityInputID = EAbilityInputID::Reload;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Use")));
}
