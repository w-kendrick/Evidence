// Fill out your copyright notice in the Description page of Project Settings.


#include "EISprintAbility.h"
#include "Evidence/Character/EvidenceCharacterMovementComponent.h"

UEISprintAbility::UEISprintAbility()
{
	AbilityInputID = EAbilityInputID::Sprint;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Sprint")));
}

void UEISprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UEvidenceCharacterMovementComponent* ECMC = Cast<UEvidenceCharacterMovementComponent>(ActorInfo->MovementComponent);
	if (ECMC)
	{
		ECMC->StartSprinting();
	}
}

void UEISprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UEvidenceCharacterMovementComponent* ECMC = Cast<UEvidenceCharacterMovementComponent>(ActorInfo->MovementComponent);
	if (ECMC)
	{
		ECMC->StopSprinting();
	}
}
