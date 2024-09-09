// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CrouchAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCrouchAbility::UCrouchAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UCrouchAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* const Character = CastChecked<ACharacter>(ActorInfo->AvatarActor);
	const UCharacterMovementComponent* const CMC = Character->GetCharacterMovement();

	if (Character->bIsCrouched || CMC->bWantsToCrouch)
	{
		Character->UnCrouch();
	}
	else if (CMC->IsMovingOnGround())
	{
		Character->Crouch();
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
