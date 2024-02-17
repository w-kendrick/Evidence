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

UCLASS(config=Game)
class AEvidenceCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	
public:
	AEvidenceCharacter();

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMoveSpeed() const;

protected:
	//Components
	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAttributeSet* CharacterAttributeSet;

	virtual void PossessedBy(AController* NewController) override;

	void InitializeAttributes();
	void AddCharacterAbilities();
	void SendASCLocalInput(const bool bIsPressed, const EAbilityInputID AbilityID);

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UEIGameplayAbility>> StartupAbilities;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

};

