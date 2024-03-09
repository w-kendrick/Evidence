// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Enums/EquipmentID.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryRequest);
DECLARE_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_MULTICAST_DELEGATE(FOnEquippedChanged);

class AEquipment;
class AEvidenceCharacter;
class AEvidenceGameState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void Pickup(AEquipment* Equipment);

	void PickupEquipped(AEquipment* NewEquipped);
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

	EEquipmentID GetEquippedType() const;
	const TArray<EEquipmentID>& GetInventory() const;

	//Delegates
	FOnInventoryRequest InventoryRequest;
	FOnInventoryChanged InventoryChanged;
	FOnEquippedChanged EquippedChanged;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetInventoryIndex(const EEquipmentID ID, const uint8 Index);

	UPROPERTY()
	AEvidenceCharacter* Char;

	UPROPERTY()
	AEvidenceGameState* EGS;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Equipped)
	AEquipment* Equipped;

	UPROPERTY(ReplicatedUsing = OnRep_Inventory)
	TArray<EEquipmentID> Inventory;

	UFUNCTION()
	void OnRep_Equipped(AEquipment* PrevEquipped);

	UFUNCTION()
	void OnRep_Inventory(TArray<EEquipmentID> NewInventory);

	bool DetermineFreeSpot(uint8& Index) const;
	void InitializeInventory();

	void DisplayInventory() const;
};
