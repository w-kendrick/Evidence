// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Delegates.h"
#include "InventoryComponent.generated.h"

class AEquipment;
class AEvidenceCharacter;
class AEvidenceGameState;
class AAmmunition;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void Pickup(AEquipment* Equipment);

	void PickupEquipped(AEquipment* const NewEquipped);
	void TryDropEquipped();
	UFUNCTION(BlueprintCallable)
	void DropEquipped();
	UFUNCTION(Server, Reliable)
	void TryEquipFromInventory(const uint8 Index);
	UFUNCTION(BlueprintCallable)
	void EquipFromInventory(const int Index);

	void PickupToInventory(AEquipment* Equipment, const uint8 Index);
	UFUNCTION(Server, Reliable)
	void TryDropFromInventory(const uint8 Index);
	UFUNCTION(BlueprintCallable)
	void DropFromInventory(const int Index);

	void ToggleInventoryWidget() const;

	bool IsAmmoAvailable(const TSubclassOf<AAmmunition> AmmoType) const;
	uint8 ConsumeAmmo(const TSubclassOf<AAmmunition> AmmoType, const uint8 Required);
	void ClearSlot(const uint8 Index);

	AEquipment* GetEquipped() const { return Equipped; }
	const TArray<AEquipment*>& GetInventory() const;

	//Delegates
	FOnInventoryRequest InventoryRequest;
	FOnInventoryChanged InventoryChanged;
	FOnEquippedChanged EquippedChanged;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetInventoryIndex(AEquipment* Equipment, const uint8 Index);

	UPROPERTY()
	AEvidenceCharacter* Char;

	UPROPERTY()
	AEvidenceGameState* EGS;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Equipped)
	AEquipment* Equipped;

	UPROPERTY(ReplicatedUsing = OnRep_Inventory)
	TArray<AEquipment*> Inventory;

	UFUNCTION()
	void OnRep_Equipped(AEquipment* PrevEquipped);

	UFUNCTION()
	void OnRep_Inventory(TArray<AEquipment*> NewInventory);

	bool DetermineFreeSpot(uint8& Index) const;
	void InitializeInventory();
};
