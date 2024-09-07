// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Evidence/Evidence.h"
#include "Components/InventoryManagerComponent.h"
#include "Evidence/Items/Equipment.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("InventoryComponent"));

	GetMesh()->bOwnerNoSee = true;
	GetMesh()->SetCollisionResponseToChannel(COLLISION_SENSE, ECollisionResponse::ECR_Block);
}

#pragma region Equipment

void ABaseCharacter::Pickup(AEquipment* const Equipment)
{
	if (InventoryManagerComponent && Equipment)
	{
		InventoryManagerComponent->Pickup(Equipment);
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
	const AEquipment* const Equipped = GetEquipped();
	if (Equipped)
	{
		return Equipped->GetWorldMesh()->GetSocketRotation(FName(TEXT("Muzzle"))).Vector();
	}

	return FVector();
}

#pragma endregion