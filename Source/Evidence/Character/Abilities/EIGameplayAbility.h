// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Evidence/Enums/AbilityInputID.h"
#include "EIGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEIGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UEIGameplayAbility();

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityInputID AbilityID = EAbilityInputID::None;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	bool bActivateAbilityOnGranted;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	bool bActivateOnInput;

	UFUNCTION(BlueprintCallable)
	bool IsInputPressed() const;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
