// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActiveGameplayEffectHandle.h"
#include "ProneCharacter.generated.h"

class UProneMovement;
class UAdvancedAbilityComponent;
class UAbilitySetupComponent;
class UGameplayEffect;
class UStaminaSet;
class UMovementSet;
struct FAbilitySet_GrantedHandles;
struct FOnAttributeChangeData;
class UCameraComponent;

UCLASS()
class PRONEMOVEMENTMODE_API AProneCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProneMovement> ProneMovement;

	friend class FSavedMove_Character_Prone;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	void SetupAttributeSetReferences();

	UFUNCTION(Client, Reliable)
	void ClientSetupAttributeSetReferences();

	UPROPERTY()
	UStaminaSet* StaminaSet;

	UPROPERTY()
	UMovementSet* MovementSet;

public:
	/** Default proned eye height */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float PronedEyeHeight;

	FORCEINLINE UProneMovement* GetProneCharacterMovement() const { return ProneMovement; }
	UAdvancedAbilityComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	UAbilitySetupComponent* GetAbilitySetupComponent() const { return AbilitySetupComponent; }
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	float GetMoveSpeed() const;

public:
	/** Set by character movement to specify that this Character is currently Proned. */
	UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_IsProned, Category = Character)
	uint32 bIsProned : 1;

public:
	AProneCharacter(const FObjectInitializer& FObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void RecalculateBaseEyeHeight() override;

	/** Handle Crouching replicated from server */
	UFUNCTION()
	virtual void OnRep_IsProned();

	/**
	 * Request the character to start Proned. The request is processed on the next update of the CharacterMovementComponent.
	 * @see OnStartProne
	 * @see IsProned
	 * @see CharacterMovement->WantsToProne
	 */
	UFUNCTION(BlueprintCallable, Category = Character, meta = (HidePin = "bClientSimulation"))
	virtual void Prone(bool bClientSimulation = false);

	/**
	 * Request the character to stop Proned. The request is processed on the next update of the CharacterMovementComponent.
	 * @see OnEndProne
	 * @see IsProned
	 * @see CharacterMovement->WantsToProne
	 */
	UFUNCTION(BlueprintCallable, Category = Character, meta = (HidePin = "bClientSimulation"))
	virtual void UnProne(bool bClientSimulation = false);

	/** @return true if this character is currently able to Prone (and is not currently Proned) */
	UFUNCTION(BlueprintCallable, Category = Character)
	virtual bool CanProne() const;

	/** Called when Character stops Proned. Called on non-owned Characters through bIsProned replication. */
	virtual void OnEndProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust);

	/** Event when Character stops Proned. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEndProne", ScriptName = "OnEndProne"))
	void K2_OnEndProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust);

	/** Called when Character Pronees. Called on non-owned Characters through bIsProned replication. */
	virtual void OnStartProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust);

	/** Event when Character Pronees. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStartProne", ScriptName = "OnStartProne"))
	void K2_OnStartProne(float HalfHeightAdjust, float ScaledHalfHeightAdjust);

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void StartSprint();
	UFUNCTION(BlueprintCallable)
	void StopSprint();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* IC) override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void AttributeSetup();

	UPROPERTY(VisibleDefaultsOnly)
	UAdvancedAbilityComponent* AbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UAbilitySetupComponent* AbilitySetupComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Movement")
	TSubclassOf<UGameplayEffect> CrouchEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Movement")
	TSubclassOf<UGameplayEffect> ProneEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Movement")
	TSubclassOf<UGameplayEffect> JumpEffectClass;

	FActiveGameplayEffectHandle ProneHandle;
	FActiveGameplayEffectHandle CrouchHandle;
	FActiveGameplayEffectHandle JumpHandle;
};