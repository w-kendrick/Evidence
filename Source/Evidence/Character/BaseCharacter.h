// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProneCharacter.h"
#include "Evidence/Delegates.h"
#include "BaseCharacter.generated.h"

class UInventoryManagerComponent;
class AEquipment;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ABaseCharacter : public AProneCharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	bool IsAlive() const;
	float GetMaxStamina() const;

	FOnStaminaChanged StaminaDelegate;
	FOnSetInteractWidgetVisibility OnSetInteractWidgetVisibility;

	virtual void Pickup(AEquipment* const Equipment);
	virtual void Drop();

	AEquipment* GetEquipped() const;

	virtual const FVector GetTraceStart() const;
	virtual const FVector GetTraceDirection() const;

	void SetInteractPromptVisibility(const bool bVisibility, const float Duration, const FString DisplayString);

	UInventoryManagerComponent* GetInventoryComponent() const { return InventoryManagerComponent; }
	FEquipmentList GetEquipmentList() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent* InventoryManagerComponent;

	virtual void AttributeSetup();

	void SetupAttributeDelegates();

	void OnStaminaChanged(const FOnAttributeChangeData& Data);
	
};
