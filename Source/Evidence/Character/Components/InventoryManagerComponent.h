// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Structs/EquipmentList.h"
#include "Evidence/Delegates.h"
#include "InventoryManagerComponent.generated.h"

enum class EUnequipType : uint8
{
	Stow,
	Drop
};

class AAmmunition;
class ABaseCharacter;

/*
 Manages a character's stored equipment
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryManagerComponent();

	FOnInventoryChanged OnInventoryChanged;
	FOnEquippedChanged OnEquippedChanged;
	FOnEquippedIndexChanged OnEquippedIndexChanged;

	void Pickup(AEquipment* const Equipment);
	void Pickup(AEquipment* const Equipment, const uint8 Index);
	void Drop(const uint8 Index);
	void DropEquipped();

	const FEquipmentList& GetInventory() const;
	AEquipment* GetEquipmentAtIndex(const uint8 Index) const;
	AEquipment* GetEquipped() const;

	bool IsAmmoAvailable(const TSubclassOf<AAmmunition>& AmmoType) const;
	uint8 ConsumeAmmo(const TSubclassOf<AAmmunition> AmmoType, const uint8 Required);

	void IncrementSelectedIndex();
	void DecrementSelectedIndex();

	void SetSelectedIndex(const uint8 Index);

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateEquipped(AEquipment* const PrevEquipped, const EUnequipType Type);

	UPROPERTY()
	ABaseCharacter* CharacterOwner;

private:
	UPROPERTY(ReplicatedUsing = OnRep_EquipmentList)
	FEquipmentList EquipmentList;

	UPROPERTY(ReplicatedUsing = OnRep_SelectedIndex)
	uint8 SelectedIndex;
	
	UFUNCTION()
	void OnRep_EquipmentList(const FEquipmentList PrevList);

	UFUNCTION()
	void OnRep_SelectedIndex(const uint8 PrevIndex);
};
