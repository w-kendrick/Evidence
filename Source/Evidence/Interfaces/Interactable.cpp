// Copyright 2020 Dan Kestranek.


#include "Interactable.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

bool IInteractable::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const
{
	return true;
}

float IInteractable::GetInteractionDuration_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return 0.0f;
}

void IInteractable::GetPreInteractSyncType_Implementation(bool& bShouldSync, EAbilityTaskNetSyncType& Type, UPrimitiveComponent* InteractionComponent) const
{
	bShouldSync = false;
	Type = EAbilityTaskNetSyncType::OnlyServerWait;
}

void IInteractable::GetPostInteractSyncType_Implementation(bool& bShouldSync, EAbilityTaskNetSyncType& Type, UPrimitiveComponent* InteractionComponent) const
{
	bShouldSync = false;
	Type = EAbilityTaskNetSyncType::OnlyServerWait;
}

FSimpleMulticastDelegate* IInteractable::GetTargetCancelInteractionDelegate(UPrimitiveComponent* InteractionComponent)
{
	return nullptr;
}

void IInteractable::RegisterInteracter_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor)
{
	if (Interacters.Contains(InteractionComponent))
	{
		TArray<AActor*>& InteractingActors = Interacters[InteractionComponent];
		if (!InteractingActors.Contains(InteractingActor))
		{
			InteractingActors.Add(InteractingActor);
		}
	}
	else
	{
		TArray<AActor*> InteractingActors;
		InteractingActors.Add(InteractingActor);
		Interacters.Add(InteractionComponent, InteractingActors);
	}
}

void IInteractable::UnregisterInteracter_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor)
{
	if (Interacters.Contains(InteractionComponent))
	{
		TArray<AActor*>& InteractingActors = Interacters[InteractionComponent];
		InteractingActors.Remove(InteractingActor);
	}
}

void IInteractable::InteractableCancelInteraction_Implementation(UPrimitiveComponent* InteractionComponent)
{
	if (Interacters.Contains(InteractionComponent))
	{
		FGameplayTagContainer InteractAbilityTagContainer;
		InteractAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.Interaction")));

		TArray<AActor*>& InteractingActors = Interacters[InteractionComponent];
		for (AActor* InteractingActor : InteractingActors)
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InteractingActor);

			if (ASC)
			{
				ASC->CancelAbilities(&InteractAbilityTagContainer);
			}
		}

		InteractingActors.Empty();
	}
}

FString IInteractable::GetInteractionString_Implementation()
{
	return FString("Press E to pickup");
}
