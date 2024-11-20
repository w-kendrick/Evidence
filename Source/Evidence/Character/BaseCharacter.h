// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProneCharacter.h"
#include "Evidence/Delegates.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.generated.h"

class UInventoryManagerComponent;
class AEquipment;
class UHealthSet;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ABaseCharacter : public AProneCharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	float GetHealth() const;
	float GetMaxHealth() const;
	bool IsAlive() const;
	float GetStamina() const;
	float GetMaxStamina() const;

	FOnStaminaChanged StaminaDelegate;
	FOnSetInteractWidgetVisibility OnSetInteractWidgetVisibility;

	virtual void Pickup(AEquipment* const Equipment);
	virtual void Pickup(AEquipment* const Equipment, const uint8 Index);
	virtual void Drop();

	UFUNCTION(BlueprintCallable)
	void DropInventory();

	AEquipment* GetEquipped() const;

	virtual const FVector GetTraceStart() const;
	virtual const FVector GetTraceDirection() const;

	void SetInteractPromptVisibility(const bool bVisibility, const float Duration, const FString DisplayString);

	void ResetAttributes();

	UInventoryManagerComponent* GetInventoryComponent() const { return InventoryManagerComponent; }
	FEquipmentList GetEquipmentList() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY()
	UHealthSet* HealthSet;

	virtual void AttributeSetup();

	void SetupAttributeDelegates();

	void OnStaminaChanged(const FOnAttributeChangeData& Data);

	FGameplayTag DefaultsTag;

private:
	void SetLookRotation();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSetLookRotation(FRotator Rotation);

	FRotator LookRotation;

	void OnMatchStateChanged(FName State);
	void EnableDamageImmunity();
	void DisableDamageImmunity();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageImmunityEffectClass;

	FActiveGameplayEffectHandle DamageImmunityHandle;
};
