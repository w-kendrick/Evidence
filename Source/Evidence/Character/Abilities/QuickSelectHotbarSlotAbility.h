// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "QuickSelectHotbarSlotAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UQuickSelectHotbarSlotAbility : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UQuickSelectHotbarSlotAbility();

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	uint8 DesiredSlot;

};
