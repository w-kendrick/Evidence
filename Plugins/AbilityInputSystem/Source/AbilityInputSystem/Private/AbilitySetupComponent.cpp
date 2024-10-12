// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySetupComponent.h"
#include "AbilityInputComponent.h"
#include "BasicGameplayTags.h"
#include "AdvancedAbilityComponent.h"
#include "AbilitySet.h"
#include "EnhancedInputSubsystems.h"

UAbilitySetupComponent::UAbilitySetupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAbilitySetupComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilitySetupComponent::InitializeAbilitySystem(const bool bApplyDefaultAbilitySet)
{
	AActor* OwningActor = GetOwner();
	UAdvancedAbilityComponent* AASC = GetAbilitySystemComponent();

	if (!AASC)
	{
		return;
	}

	AASC->InitAbilityActorInfo(OwningActor, OwningActor);

	checkf(DefaultAbilitySet, TEXT("DefaultAbilitySet is null"));
	if (bApplyDefaultAbilitySet)
	{
		AddAbilitySet(DefaultAbilitySet);
	}
}

void UAbilitySetupComponent::AddAbilitySet(TObjectPtr<const UAbilitySet> Set)
{
	AActor* OwningActor = GetOwner();
	UAdvancedAbilityComponent* AASC = GetAbilitySystemComponent();

	FAbilitySet_GrantedHandles Handles;
	Set.Get()->GiveToAbilitySystem(AASC, &Handles, OwningActor);
}

void UAbilitySetupComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	UAbilityInputComponent* AbilityInputComponent = Cast<UAbilityInputComponent>(PlayerInputComponent);
	checkf(AbilityInputComponent, TEXT("Not using UAbilityInputComponent (set in Project Settings)"));
	if (AbilityInputComponent)
	{
		checkf(InputConfig, TEXT("InputConfig is null"));
		AbilityInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased);

		AbilityInputComponent->BindNativeAction(InputConfig, BasicGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		AbilityInputComponent->BindNativeAction(InputConfig, BasicGameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse);;
	}
}

void UAbilitySetupComponent::AddInputMappingContext(ULocalPlayer* LocalPlayer)
{
	if (UEnhancedInputLocalPlayerSubsystem* const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		checkf(InputMappingContext, TEXT("InputMappingContext is null"));
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void UAbilitySetupComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (UAdvancedAbilityComponent* AASC = GetAbilitySystemComponent())
	{
		AASC->AbilityInputTagPressed(InputTag);
	}
}

void UAbilitySetupComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (UAdvancedAbilityComponent* AASC = GetAbilitySystemComponent())
	{
		AASC->AbilityInputTagReleased(InputTag);
	}
}

void UAbilitySetupComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = Cast<APawn>(GetOwner());
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UAbilitySetupComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = Cast<APawn>(GetOwner());

	if (!Pawn)
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

UAdvancedAbilityComponent* UAbilitySetupComponent::GetAbilitySystemComponent() const
{
	UAdvancedAbilityComponent* Comp = nullptr;

	AActor* OwningActor = GetOwner();
	if (OwningActor)
	{
		Comp = OwningActor->FindComponentByClass<UAdvancedAbilityComponent>();
	}

	return Comp;
}
