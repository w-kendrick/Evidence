// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfig.h"

/*
	Retrieves the input action related to the given gameplay tag for a native action
	@param InputTag: The gameplay tag to lookup
	@return The related input action
*/
const UInputAction* UInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FAbilityInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}

/*
	Retrieves the input action related to the given gameplay tag for a gameplay ability
	@param InputTag: The gameplay tag to lookup
	@return The related input action
*/
const UInputAction* UInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FAbilityInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}
