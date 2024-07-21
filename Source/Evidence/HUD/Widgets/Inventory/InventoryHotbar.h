// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Structs/EquipmentList.h"
#include "InventoryHotbar.generated.h"

/**
Widget for showing the equipment stored in player inventory
 */
UCLASS()
class EVIDENCE_API UInventoryHotbar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SetupDelegate(APawn* OldPawn, APawn* NewPawn);

	void OnInventoryChanged(FEquipmentList EquipmentList);
	
};
