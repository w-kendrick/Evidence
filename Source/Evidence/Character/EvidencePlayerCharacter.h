// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvidenceCharacter.h"
#include "EvidencePlayerCharacter.generated.h"

class UInputAction;

UCLASS()
class EVIDENCE_API AEvidencePlayerCharacter : public AEvidenceCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	//Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;

public:
	AEvidencePlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Pickup(AEquipment* Equipment) override;

	UFUNCTION(BlueprintCallable)
	void ShowInteractPrompt(const float Duration);

	UFUNCTION(BlueprintCallable)
	void HideInteractPrompt();

	UFUNCTION(BlueprintCallable)
	void StartInteractionTimer(const float Duration);

	UFUNCTION(BlueprintCallable)
	void StopInteractionTimer();

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleJumpActionPressed();
	void HandleJumpActionReleased();
	void HandleSprintActionPressed();
	void HandleSprintActionReleased();
	void HandleCrouchActionPressed();
	void HandleCrouchActionReleased();
	void HandleInteractActionPressed();
	void HandleInteractActionReleased();
	void HandleDropActionPressed();
	void HandleDropActionReleased();

public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};
