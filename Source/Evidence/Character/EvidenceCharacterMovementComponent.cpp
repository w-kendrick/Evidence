// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceCharacterMovementComponent.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

#pragma region Saved Move

UEvidenceCharacterMovementComponent::FSavedMove_Evidence::FSavedMove_Evidence()
{
	Saved_bWantsToSprint = 0;
}

bool UEvidenceCharacterMovementComponent::FSavedMove_Evidence::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_Evidence* NewEvidenceMove = static_cast<FSavedMove_Evidence*>(NewMove.Get());

	if (Saved_bWantsToSprint != NewEvidenceMove->Saved_bWantsToSprint)
	{
		return false;
	}

	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void UEvidenceCharacterMovementComponent::FSavedMove_Evidence::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}

uint8 UEvidenceCharacterMovementComponent::FSavedMove_Evidence::GetCompressedFlags() const
{
	uint8 Result = FSavedMove_Character::GetCompressedFlags();

	if (Saved_bWantsToSprint) Result |= FLAG_Sprint;

	return Result;
}

void UEvidenceCharacterMovementComponent::FSavedMove_Evidence::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const UEvidenceCharacterMovementComponent* CharacterMovement = Cast<UEvidenceCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

void UEvidenceCharacterMovementComponent::FSavedMove_Evidence::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);

	UEvidenceCharacterMovementComponent* CharacterMovement = Cast<UEvidenceCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}
#pragma endregion

#pragma region Client Network Prediction Data

UEvidenceCharacterMovementComponent::FNetworkPredictionData_Client_Evidence::FNetworkPredictionData_Client_Evidence(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UEvidenceCharacterMovementComponent::FNetworkPredictionData_Client_Evidence::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Evidence());
}

#pragma endregion

#pragma region CMC

UEvidenceCharacterMovementComponent::UEvidenceCharacterMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
	EvidenceServerMoveBitWriter.SetAllowResize(true);
}

FNetworkPredictionData_Client* UEvidenceCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

		if (ClientPredictionData == nullptr)
		{
			UEvidenceCharacterMovementComponent* MutableThis = const_cast<UEvidenceCharacterMovementComponent*>(this);

			MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Evidence(*this);
			MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
			MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
		}
	return ClientPredictionData;
}

bool UEvidenceCharacterMovementComponent::IsMovementMode(EMovementMode InMovementMode) const
{
	return InMovementMode == MovementMode;
}

bool UEvidenceCharacterMovementComponent::CanCrouchInCurrentState() const
{
	return Super::CanCrouchInCurrentState() && IsMovingOnGround();
}

float UEvidenceCharacterMovementComponent::GetMaxSpeed() const
{
	if (Safe_bWantsToSprint && IsMovingForward() && !IsCrouching()) return MaxSprintSpeed;

	return Super::GetMaxSpeed();
}

bool UEvidenceCharacterMovementComponent::IsMovingForward() const
{
	if (!PawnOwner)
	{
		return false;
	}

	FVector Forward = PawnOwner->GetActorForwardVector();
	FVector MoveDirection = Velocity.GetSafeNormal();

	//Ignore vertical movement
	Forward.Z = 0.0f;
	MoveDirection.Z = 0.0f;

	float VelocityDot = FVector::DotProduct(Forward, MoveDirection);
	return VelocityDot > 0.7f;
}

void UEvidenceCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	if (Safe_bWantsToSprint && IsCrouching())
	{
		bWantsToCrouch = false;
	}

	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

void UEvidenceCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	EvidenceCharacterOwner = Cast<AEvidenceCharacter>(GetOwner());
}

void UEvidenceCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Evidence::FLAG_Sprint) != 0;
}

void UEvidenceCharacterMovementComponent::CallServerMovePacked(const FSavedMove_Character* NewMove, const FSavedMove_Character* PendingMove, const FSavedMove_Character* OldMove)
{
	// Get storage container we'll be using and fill it with movement data
	FCharacterNetworkMoveDataContainer& MoveDataContainer = GetNetworkMoveDataContainer();
	MoveDataContainer.ClientFillNetworkMoveData(NewMove, PendingMove, OldMove);

	// Reset bit writer without affecting allocations
	FBitWriterMark BitWriterReset;
	BitWriterReset.Pop(EvidenceServerMoveBitWriter);

	// 'static' to avoid reallocation each invocation
	static FCharacterServerMovePackedBits PackedBits;
	UNetConnection* NetConnection = CharacterOwner->GetNetConnection();


	{
		// Extract the net package map used for serializing object references.
		EvidenceServerMoveBitWriter.PackageMap = NetConnection ? ToRawPtr(NetConnection->PackageMap) : nullptr;
	}

	if (EvidenceServerMoveBitWriter.PackageMap == nullptr)
	{
		UE_LOG(LogNetPlayerMovement, Error, TEXT("CallServerMovePacked: Failed to find a NetConnection/PackageMap for data serialization!"));
		return;
	}

	// Serialize move struct into a bit stream
	if (!MoveDataContainer.Serialize(*this, EvidenceServerMoveBitWriter, EvidenceServerMoveBitWriter.PackageMap) || EvidenceServerMoveBitWriter.IsError())
	{
		UE_LOG(LogNetPlayerMovement, Error, TEXT("CallServerMovePacked: Failed to serialize out movement data!"));
		return;
	}

	// Copy bits to our struct that we can NetSerialize to the server.
	PackedBits.DataBits.SetNumUninitialized(EvidenceServerMoveBitWriter.GetNumBits());

	check(PackedBits.DataBits.Num() >= EvidenceServerMoveBitWriter.GetNumBits());
	FMemory::Memcpy(PackedBits.DataBits.GetData(), EvidenceServerMoveBitWriter.GetData(), EvidenceServerMoveBitWriter.GetNumBytes());

	// Send bits to server!
	ServerMovePacked_ClientSend(PackedBits);

	MarkForClientCameraUpdate();
}

#pragma endregion

#pragma region Input

void UEvidenceCharacterMovementComponent::StartSprinting()
{
	Safe_bWantsToSprint = true;
}

void UEvidenceCharacterMovementComponent::StopSprinting()
{
	Safe_bWantsToSprint = false;
}

#pragma endregion