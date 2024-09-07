// Fill out your copyright notice in the Description page of Project Settings.


#include "ProneCharacter.h"

#include "Net/UnrealNetwork.h"
#include "ProneMovement.h"
#include "AdvancedAbilityComponent.h"
#include "AbilitySetupComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySet.h"
#include "GameplayEffect.h"
#include "AttributeSets/StaminaSet.h"
#include "AttributeSets/MovementSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProneCharacter)

AProneCharacter::AProneCharacter(const FObjectInitializer& FObjectInitializer)
	: Super(FObjectInitializer.SetDefaultSubobjectClass<UProneMovement>(CharacterMovementComponentName))
{
	ProneMovement = Cast<UProneMovement>(GetCharacterMovement());

	AbilitySystemComponent = CreateDefaultSubobject<UAdvancedAbilityComponent>(TEXT("AbilitySystemComponent"));

	AbilitySetupComponent = CreateDefaultSubobject<UAbilitySetupComponent>(TEXT("AbilitySetupComponent"));

	GetMesh()->bOwnerNoSee = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	PronedEyeHeight = 30.f;
}

void AProneCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, bIsProned, COND_SimulatedOnly);
}

void AProneCharacter::RecalculateBaseEyeHeight()
{
	if (bIsProned)
	{
		BaseEyeHeight = PronedEyeHeight;
	}
	else
	{
		Super::RecalculateBaseEyeHeight();
	}
}

void AProneCharacter::OnRep_IsProned()
{
	if (ProneMovement)
	{
		if (bIsProned)
		{
			ProneMovement->bWantsToProne = true;
			ProneMovement->Prone(true);
		}
		else
		{
			ProneMovement->bWantsToProne = false;
			ProneMovement->UnProne(true);
		}
		ProneMovement->bNetworkUpdateReceived = true;
	}
}

void AProneCharacter::Prone(bool bClientSimulation)
{
	if (ProneMovement)
	{
		if (CanProne())
		{
			ProneMovement->bWantsToProne = true;
		}
	}
}

void AProneCharacter::UnProne(bool bClientSimulation)
{
	if (ProneMovement)
	{
		ProneMovement->bWantsToProne = false;
	}
}

bool AProneCharacter::CanProne() const
{
	return !bIsProned && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void AProneCharacter::OnEndProne(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();

	if (!bIsCrouched)
	{
		const ACharacter* DefaultChar = GetDefault<ACharacter>(GetClass());
		if (GetMesh() && DefaultChar->GetMesh())
		{
			FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
			MeshRelativeLocation.Z = DefaultChar->GetMesh()->GetRelativeLocation().Z;
			BaseTranslationOffset.Z = MeshRelativeLocation.Z;
		}
		else
		{
			BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z;
		}
	}
	K2_OnEndProne(HeightAdjust, ScaledHeightAdjust);

	if (AbilitySystemComponent && ProneHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(ProneHandle);
	}
}

void AProneCharacter::OnStartProne(float HeightAdjust, float ScaledHeightAdjust)
{
	RecalculateBaseEyeHeight();

	const ACharacter* DefaultChar = GetDefault<ACharacter>(GetClass());
	if (GetMesh() && DefaultChar->GetMesh())
	{
		FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultChar->GetMesh()->GetRelativeLocation().Z + HeightAdjust;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z + HeightAdjust;
	}

	K2_OnStartProne(HeightAdjust, ScaledHeightAdjust);

	if (AbilitySystemComponent)
	{
		const UGameplayEffect* ProneEffect = ProneEffectClass->GetDefaultObject<UGameplayEffect>();
		ProneHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(ProneEffect, 1, AbilitySystemComponent->MakeEffectContext());
	}
}

void AProneCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	if (AbilitySystemComponent)
	{
		const UGameplayEffect* CrouchEffect = CrouchEffectClass->GetDefaultObject<UGameplayEffect>();
		CrouchHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(CrouchEffect, 1, AbilitySystemComponent->MakeEffectContext());
	}
}

void AProneCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	if (AbilitySystemComponent && CrouchHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchHandle);
	}
}

void AProneCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	if (AbilitySystemComponent)
	{
		const UGameplayEffect* JumpEffect = JumpEffectClass->GetDefaultObject<UGameplayEffect>();
		JumpHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(JumpEffect, 1, AbilitySystemComponent->MakeEffectContext());
	}
}

void AProneCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (AbilitySystemComponent && JumpHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(JumpHandle);
	}
}

void AProneCharacter::StartSprint()
{
	if (ProneMovement)
	{
		ProneMovement->bWantsToSprint = true;
		ProneMovement->bWantsToCrouch = false;
		ProneMovement->bWantsToProne = false;
	}
}

void AProneCharacter::StopSprint()
{
	if (ProneMovement)
	{
		ProneMovement->bWantsToSprint = false;
	}
}

void AProneCharacter::SetupPlayerInputComponent(UInputComponent* IC)
{
	Super::SetupPlayerInputComponent(IC);

	AbilitySetupComponent->InitializePlayerInput(IC);
}

void AProneCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySetupComponent->InitializeAbilitySystem(true);

	SetupAttributeSetReferences();
}

void AProneCharacter::SetupAttributeSetReferences()
{
	AttributeSetup();

	ClientSetupAttributeSetReferences();
}

void AProneCharacter::AttributeSetup()
{
	MovementSet = AbilitySystemComponent->GetSpawnedAttribute<UMovementSet>();
	StaminaSet = AbilitySystemComponent->GetSpawnedAttribute<UStaminaSet>();
}

void AProneCharacter::ClientSetupAttributeSetReferences_Implementation()
{
	AttributeSetup();
}

float AProneCharacter::GetMoveSpeed() const
{
	if (MovementSet)
	{
		return MovementSet->GetMovementSpeed();
	}
	return 0.0f;
}