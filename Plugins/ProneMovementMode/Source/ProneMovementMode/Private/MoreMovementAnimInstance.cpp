// Fill out your copyright notice in the Description page of Project Settings.


#include "MoreMovementAnimInstance.h"
#include "ProneCharacter.h"
#include "AdvancedAbilityComponent.h"

void UMoreMovementAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MoreMovementCharacter = Cast<AProneCharacter>(TryGetPawnOwner());
}

void UMoreMovementAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MoreMovementCharacter)
	{
		Speed = MoreMovementCharacter->GetVelocity().Length();
		Direction = CalculateDirection(MoreMovementCharacter->GetVelocity(), MoreMovementCharacter->GetViewRotation());
		Mode = GetMovementMode();
	}
}

EMoreMovementMode UMoreMovementAnimInstance::GetMovementMode() const
{
	if (MoreMovementCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("MovementMode.Sprint")))
	{
		return EMoreMovementMode::Sprint;
	}
	else if (MoreMovementCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("MovementMode.Crouch")))
	{
		return EMoreMovementMode::Crouch;
	}
	else if (MoreMovementCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("MovementMode.Prone")))
	{
		return EMoreMovementMode::Prone;
	}
	else if (MoreMovementCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("MovementMode.Jump")))
	{
		return EMoreMovementMode::Jump;
	}
	else
	{
		return EMoreMovementMode::Walk;
	}
}
