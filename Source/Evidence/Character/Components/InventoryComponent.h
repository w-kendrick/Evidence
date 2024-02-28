// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Enums/EquipmentID.h"
#include "InventoryComponent.generated.h"

class AEquipment;
class AEvidenceCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void PickupEquipped(AEquipment* NewEquipped);
	void DropEquipped();

	void PickupToInventory(AEquipment* NewEquipped);

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetInventoryIndex(const EEquipmentID ID, const uint8 Index);

	UPROPERTY()
	AEvidenceCharacter* Char;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Equipped)
	AEquipment* Equipped;

	UPROPERTY(ReplicatedUsing = OnRep_Inventory)
	TArray<EEquipmentID> Inventory;

	UFUNCTION()
	void OnRep_Equipped(AEquipment* PrevEquipped);

	UFUNCTION()
	void OnRep_Inventory(TArray<EEquipmentID> NewInventory);
};
