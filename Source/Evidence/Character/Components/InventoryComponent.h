// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

	UPROPERTY()
	AEvidenceCharacter* Char;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Equipped)
	AEquipment* Equipped;

	UFUNCTION()
	void OnRep_Equipped(AEquipment* PrevEquipped);
};
