// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/AttributeSets/CharacterAttributeSet.h"
#include "Evidence/Enums/AbilityInputID.h"
#include "EvidenceCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UEvidenceCharacterMovementComponent;

UCLASS(config=Game)
class AEvidenceCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	
public:
	AEvidenceCharacter(const FObjectInitializer& ObjectInitializer);

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMoveSpeed() const;
	bool IsAlive() const;

protected:
	//Components
	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	UEvidenceCharacterMovementComponent* EvidenceCMC;

	virtual void PossessedBy(AController* NewController) override;

	void InitializeAttributes();
	void AddCharacterAbilities();
	void AddStartupEffects();
	void SendASCLocalInput(const bool bIsPressed, const EAbilityInputID AbilityID);

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UEIGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

};

