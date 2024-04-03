// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/AttributeSets/CharacterAttributeSet.h"
#include "Evidence/Enums/AbilityInputID.h"
#include "GameplayEffectTypes.h"
#include "EvidenceCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UEvidenceCharacterMovementComponent;
class UInventoryComponent;
class AEquipment;
class UHealthComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FStaminaChange, float);

UCLASS(config=Game)
class AEvidenceCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	
public:
	AEvidenceCharacter(const FObjectInitializer& ObjectInitializer);

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;
	float GetMoveSpeed() const;
	bool IsAlive() const;

	FStaminaChange StaminaDelegate;

	virtual void Pickup(AEquipment* Equipment);
	virtual void Drop();

	AEquipment* GetEquipped() const;

	virtual const FVector GetTraceStart() const;
	virtual const FVector GetTraceDirection() const;

protected:
	//Components
	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	UEvidenceCharacterMovementComponent* EvidenceCMC;

	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* HealthComponent;

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	void InitializeAttributes();
	void AddCharacterAbilities();
	void AddStartupEffects();
	void SetupDelegates();
	void SendASCLocalInput(const bool bIsPressed, const EAbilityInputID AbilityID);

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UEIGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	void OnStaminaChanged(const FOnAttributeChangeData& Data);

public:
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

};

