// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Enums/EquipmentID.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryRequest);

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
	void EquipFromInventory(const uint8 Index);

	void PickupToInventory(AEquipment* NewEquipped, const uint8 Index);
	void DropFromInventory(const uint8 Index);

	void ToggleInventoryWidget();

	EEquipmentID GetEquippedType() const;
	const TArray<EEquipmentID>& GetInventory() const;

	//Delegates
	FOnInventoryRequest InventoryRequest;

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
};
