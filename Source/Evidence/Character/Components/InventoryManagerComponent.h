// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evidence/Structs/EquipmentList.h"
#include "InventoryManagerComponent.generated.h"

/*
 Manages a character's stored equipment
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryManagerComponent();

	void Pickup(AEquipment* Equipment, const uint8 Index);
	void Drop(const uint8 Index);

	AEquipment* GetEquipped() const;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_EquipmentList)
	FEquipmentList EquipmentList;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedIndex)
	uint8 EquippedIndex;
	
	UFUNCTION()
	void OnRep_EquipmentList(const FEquipmentList PrevList);

	UFUNCTION()
	void OnRep_EquippedIndex(const uint8 PrevIndex);
};
