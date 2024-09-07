// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHotbarSlot.generated.h"

class AEquipment;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UInventoryHotbarSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateSlot(const AEquipment* const Equipment);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
};
