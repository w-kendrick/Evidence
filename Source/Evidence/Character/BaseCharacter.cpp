// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Evidence/Evidence.h"
#include "Components/InventoryManagerComponent.h"
#include "Evidence/Items/Equipment.h"
#include "AttributeSets/StaminaSet.h"
#include "AttributeSets/HealthSet.h"
#include "AbilitySystemBlueprintLibrary.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("InventoryComponent"));

	GetMesh()->bOwnerNoSee = true;
	GetMesh()->SetCollisionResponseToChannel(COLLISION_SENSE, ECollisionResponse::ECR_Block);

	DefaultsTag = FGameplayTag::RequestGameplayTag("GameplayEvent.Defaults");
}

#pragma region Attributes

void ABaseCharacter::AttributeSetup()
{
	Super::AttributeSetup();

	HealthSet = AbilitySystemComponent->GetSpawnedAttribute<UHealthSet>();

	SetupAttributeDelegates();
}

void ABaseCharacter::SetupAttributeDelegates()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(StaminaSet->GetStaminaAttribute()).AddUObject(this, &ThisClass::OnStaminaChanged);
}

void ABaseCharacter::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	StaminaDelegate.Broadcast(Data.NewValue);
}

bool ABaseCharacter::IsAlive() const
{
	if (HealthSet)
	{
		return HealthSet->IsAlive();
	}
	return false;
}

float ABaseCharacter::GetMaxStamina() const
{
	if (StaminaSet)
	{
		return StaminaSet->GetMaxStamina();
	}
	return 0.0f;
}

#pragma endregion

#pragma region Equipment

void ABaseCharacter::Pickup(AEquipment* const Equipment)
{
	if (InventoryManagerComponent && Equipment)
	{
		InventoryManagerComponent->Pickup(Equipment);
	}
}

void ABaseCharacter::Pickup(AEquipment* const Equipment, const uint8 Index)
{
	if (InventoryManagerComponent && Equipment)
	{
		InventoryManagerComponent->Pickup(Equipment, Index);
	}
}

void ABaseCharacter::Drop()
{
	if (InventoryManagerComponent)
	{
		InventoryManagerComponent->DropEquipped();
	}
}

AEquipment* ABaseCharacter::GetEquipped() const
{
	if (!InventoryManagerComponent)
	{
		return nullptr;
	}

	return InventoryManagerComponent->GetEquipped();
}

#pragma endregion

#pragma region Trace

const FVector ABaseCharacter::GetTraceStart() const
{
	const AEquipment* const Equipped = GetEquipped();
	if (Equipped)
	{
		return Equipped->GetWorldMesh()->GetSocketLocation(FName(TEXT("Muzzle")));
	}

	return FVector();
}

const FVector ABaseCharacter::GetTraceDirection() const
{
	return GetViewRotation().Vector();
}

#pragma endregion

void ABaseCharacter::SetInteractPromptVisibility(const bool bVisibility, const float Duration, const FString DisplayString)
{
	OnSetInteractWidgetVisibility.ExecuteIfBound(bVisibility, Duration, DisplayString);
}

void ABaseCharacter::ResetAttributes()
{
	if (HealthSet)
	{
		HealthSet->Respawn();
	}

	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, DefaultsTag, Data);
}

FEquipmentList ABaseCharacter::GetEquipmentList() const
{
	return InventoryManagerComponent->GetInventory();
}
