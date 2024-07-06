// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidencePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Evidence/EvidencePlayerController.h"
#include "Components/InventoryComponent.h"

#pragma region Class Essentials

AEvidencePlayerCharacter::AEvidencePlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AEvidencePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* const PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		PlayerController->SetInputMode(FInputModeGameOnly());
	}

}

#pragma endregion

#pragma region Input

void AEvidencePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::HandleJumpActionPressed);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::HandleJumpActionReleased);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::HandleSprintActionPressed);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::HandleSprintActionReleased);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ThisClass::HandleCrouchActionPressed);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ThisClass::HandleCrouchActionReleased);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::HandleInteractActionPressed);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ThisClass::HandleInteractActionReleased);

		// Dropping
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &ThisClass::HandleDropActionPressed);
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Completed, this, &ThisClass::HandleDropActionReleased);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ThisClass::HandleInventoryActionPressed);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Completed, this, &ThisClass::HandleInventoryActionReleased);

		// Use equipment
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &ThisClass::HandleUseActionPressed);
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Completed, this, &ThisClass::HandleUseActionReleased);

		// Reload equipment
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ThisClass::HandleReloadActionPressed);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, this, &ThisClass::HandleReloadActionReleased);

		// Underbarrel equipment
		EnhancedInputComponent->BindAction(UnderbarrelAction, ETriggerEvent::Started, this, &ThisClass::HandleUnderbarrelActionPressed);
		EnhancedInputComponent->BindAction(UnderbarrelAction, ETriggerEvent::Completed, this, &ThisClass::HandleUnderbarrelActionReleased);
	}
}

void AEvidencePlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEvidencePlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEvidencePlayerCharacter::HandleJumpActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Jump);
}

void AEvidencePlayerCharacter::HandleJumpActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Jump);
}

void AEvidencePlayerCharacter::HandleSprintActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Sprint);
}

void AEvidencePlayerCharacter::HandleSprintActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Sprint);
}

void AEvidencePlayerCharacter::HandleCrouchActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Crouch);
}

void AEvidencePlayerCharacter::HandleCrouchActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Crouch);
}

void AEvidencePlayerCharacter::HandleInteractActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Interact);
}

void AEvidencePlayerCharacter::HandleInteractActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Interact);
}

void AEvidencePlayerCharacter::HandleDropActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Drop);
}

void AEvidencePlayerCharacter::HandleDropActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Drop);
}

void AEvidencePlayerCharacter::HandleInventoryActionPressed()
{
	if (InventoryComponent)
	{
		InventoryComponent->ToggleInventoryWidget();
	}
}

void AEvidencePlayerCharacter::HandleInventoryActionReleased()
{

}

void AEvidencePlayerCharacter::HandleUseActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Use);
}

void AEvidencePlayerCharacter::HandleUseActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Use);
}

void AEvidencePlayerCharacter::HandleReloadActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Reload);
}

void AEvidencePlayerCharacter::HandleReloadActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Reload);
}

void AEvidencePlayerCharacter::HandleUnderbarrelActionPressed()
{
	SendASCLocalInput(true, EAbilityInputID::Underbarrel);
}

void AEvidencePlayerCharacter::HandleUnderbarrelActionReleased()
{
	SendASCLocalInput(false, EAbilityInputID::Underbarrel);
}

#pragma endregion

#pragma region Interaction

void AEvidencePlayerCharacter::ShowInteractPrompt(const float Duration)
{
	if (AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Controller))
	{
		EPC->ShowInteractPrompt(Duration);
	}
}

void AEvidencePlayerCharacter::HideInteractPrompt()
{
	if (AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Controller))
	{
		EPC->HideInteractPrompt();
	}
}

void AEvidencePlayerCharacter::StartInteractionTimer(const float Duration)
{
	if (AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Controller))
	{
		EPC->StartInteractionTimer(Duration);
	}
}

void AEvidencePlayerCharacter::StopInteractionTimer()
{
	if (AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Controller))
	{
		EPC->StopInteractionTimer();
	}
}

#pragma endregion

#pragma region Trace

const FVector AEvidencePlayerCharacter::GetTraceStart() const
{
	return FirstPersonCameraComponent->GetComponentLocation();
}

const FVector AEvidencePlayerCharacter::GetTraceDirection() const
{
	return FirstPersonCameraComponent->GetForwardVector();
}

#pragma endregion