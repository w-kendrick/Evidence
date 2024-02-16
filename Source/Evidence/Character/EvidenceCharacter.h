// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/AttributeSets/CharacterAttributeSet.h"
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

private:
	//Components
	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAttributeSet* CharacterAttributeSet;
	
public:
	AEvidenceCharacter();

	float GetHealth() const;
	float GetMaxHealth() const;

protected:
	virtual void PossessedBy(AController* NewController) override;

	void InitializeAttributes();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

};

