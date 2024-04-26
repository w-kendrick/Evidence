// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentStatWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UEquipmentStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void OnEquippedChanged(AEquipment* Current, AEquipment* Previous);
	
};