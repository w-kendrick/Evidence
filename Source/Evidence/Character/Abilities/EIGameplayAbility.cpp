// Fill out your copyright notice in the Description page of Project Settings.


#include "EIGameplayAbility.h"
#include "AbilitySystemComponent.h"

UEIGameplayAbility::UEIGameplayAbility()
{
	bActivateAbilityOnGranted = false;
	bActivateOnInput = true;
}

bool UEIGameplayAbility::IsInputPressed() const
{
	const FGameplayAbilitySpec* const Spec = GetCurrentAbilitySpec();
	return Spec && Spec->InputPressed;
}

void UEIGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		const bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
