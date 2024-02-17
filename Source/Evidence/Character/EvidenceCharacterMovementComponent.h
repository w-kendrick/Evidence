// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EvidenceCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEvidenceCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_Evidence : public FSavedMove_Character
	{
	public:
		enum CompressedFlags
		{
			FLAG_Sprint = 0x10,
			FLAG_Custom_1 = 0x20,
			FLAG_Custom_2 = 0x40,
			FLAG_Custom_3 = 0x80,
		};

		// Flags
		uint8 Saved_bWantsToSprint : 1;


		FSavedMove_Evidence();

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};
	
	class FNetworkPredictionData_Client_Evidence : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_Evidence(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

	UPROPERTY(Transient) class AEvidenceCharacter* EvidenceCharacterOwner;

	// Flags
	bool Safe_bWantsToSprint;

public:
	UEvidenceCharacterMovementComponent();
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	bool IsMovementMode(EMovementMode InMovementMode) const;

	virtual bool CanCrouchInCurrentState() const override;
	virtual float GetMaxSpeed() const override;
	bool IsMovingForward() const;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

protected:
	virtual void InitializeComponent() override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual void CallServerMovePacked(const FSavedMove_Character* NewMove, const FSavedMove_Character* PendingMove, const FSavedMove_Character* OldMove) override;
	FNetBitWriter EvidenceServerMoveBitWriter;

	//Sprint
	UPROPERTY(EditDefaultsOnly) float MaxSprintSpeed = 1000.f;

//Input
public:
	void StartSprinting();
	void StopSprinting();
};
