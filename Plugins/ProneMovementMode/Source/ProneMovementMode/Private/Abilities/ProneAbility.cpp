// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ProneAbility.h"
#include "ProneCharacter.h"
#include "ProneMovement.h"

UProneAbility::UProneAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UProneAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AProneCharacter* const Character = CastChecked<AProneCharacter>(ActorInfo->AvatarActor);
	const UProneMovement* const CMC = Character->GetProneCharacterMovement();

	if (Character->bIsProned || CMC->bWantsToProne)
	{
		Character->UnProne();
	}
	else if (CMC->IsMovingOnGround())
	{
		Character->Prone();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
