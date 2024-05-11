// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Abilities/EIGameplayAbility.h"
#include "Components/EvidenceCharacterMovementComponent.h"
#include "Components/InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Evidence.h"

#pragma region Class Essentials

AEvidenceCharacter::AEvidenceCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEvidenceCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	EvidenceCMC = Cast<UEvidenceCharacterMovementComponent>(GetCharacterMovement());

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("CharacterAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	GetMesh()->bOwnerNoSee = true;
	GetMesh()->SetCollisionResponseToChannel(COLLISION_SENSE, ECollisionResponse::ECR_Block);
}

void AEvidenceCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupDelegates();
}

#pragma endregion

#pragma region Abilities

void AEvidenceCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		InitializeAttributes();
		AddCharacterAbilities();
		AddStartupEffects();
	}
}

void AEvidenceCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		(void)AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void AEvidenceCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent)
	{
		return;
	}

	for (const TSubclassOf<UEIGameplayAbility>& Ability : StartupAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 0, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->bAbilitiesGiven = true;
}

void AEvidenceCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		const FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 0, EffectContext);
		if (NewHandle.IsValid())
		{
			(void)AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AEvidenceCharacter::SetupDelegates()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaAttribute()).AddUObject(this, &ThisClass::OnStaminaChanged);
}

void AEvidenceCharacter::SendASCLocalInput(const bool bIsPressed, const EAbilityInputID AbilityID)
{
	if (!AbilitySystemComponent) return;

	if (bIsPressed)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityID));
	}
	else
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityID));
	}
}

void AEvidenceCharacter::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	StaminaDelegate.Broadcast(Data.NewValue);
}

#pragma endregion

#pragma region Getters

float AEvidenceCharacter::GetHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetHealth();
	}
	return 0.0f;
}

float AEvidenceCharacter::GetMaxHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float AEvidenceCharacter::GetStamina() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetStamina();
	}
	return 0.0f;
}

float AEvidenceCharacter::GetMaxStamina() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

float AEvidenceCharacter::GetMoveSpeed() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMoveSpeed();
	}
	return 0.0f;
}

bool AEvidenceCharacter::IsAlive() const
{
	return GetHealth() > 0;
}

#pragma endregion

#pragma region Equipment

void AEvidenceCharacter::Pickup(AEquipment* const Equipment)
{
	if (InventoryComponent && Equipment)
	{
		InventoryComponent->Pickup(Equipment);
	}
}

void AEvidenceCharacter::Drop()
{
	if (InventoryComponent)
	{
		InventoryComponent->DropEquipped();
	}
}

AEquipment* AEvidenceCharacter::GetEquipped() const
{
	if (!InventoryComponent)
	{
		return nullptr;
	}

	return InventoryComponent->GetEquipped();
}

#pragma endregion

#pragma region Trace

const FVector AEvidenceCharacter::GetTraceStart() const
{
	const AEquipment* const Equipped = GetEquipped();
	if (Equipped)
	{
		return Equipped->GetWorldMesh()->GetSocketLocation(FName("Muzzle"));
	}

	return FVector();
}

const FVector AEvidenceCharacter::GetTraceDirection() const
{
	const AEquipment* const Equipped = GetEquipped();
	if (Equipped)
	{
		return Equipped->GetWorldMesh()->GetSocketRotation(FName("Muzzle")).Vector();
	}

	return FVector();
}

#pragma endregion