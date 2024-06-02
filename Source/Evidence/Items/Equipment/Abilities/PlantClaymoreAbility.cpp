// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantClaymoreAbility.h"
#include "Evidence/Items/Equipment/Claymore.h"
#include "AbilitySystemBlueprintLibrary.h"

void UPlantClaymoreAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	AClaymore* const Claymore = Cast<AClaymore>(GetSourceObject(Handle, ActorInfo));
	if (!Claymore)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ActorInfo->AvatarActor.Get(), FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Drop"))), Payload);

	const FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel());
	Claymore->DamageEffectHandle = DamageEffectSpecHandle;
	Claymore->Plant();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
