// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputConfig.h"
#include "AbilitySetupComponent.generated.h"

struct FInputActionValue;
struct FAbilitySet_GrantedHandles;
class UAdvancedAbilityComponent;
class UAbilitySet;
class UInputMappingContext;
class ULocalPlayer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABILITYINPUTSYSTEM_API UAbilitySetupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilitySetupComponent();

	void InitializeAbilitySystem(const bool bApplyDefaultAbilitySet = false);
	void AddAbilitySet(TObjectPtr<const UAbilitySet> Set);
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	void AddInputMappingContext(ULocalPlayer* LocalPlayer);

protected:
	virtual void BeginPlay() override;

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);

	UAdvancedAbilityComponent* GetAbilitySystemComponent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<const UAbilitySet> DefaultAbilitySet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
		
};
