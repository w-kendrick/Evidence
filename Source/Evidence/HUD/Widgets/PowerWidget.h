// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UPowerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void OnEquippedChanged(AEquipment* Current, AEquipment* Previous);
	void OnPowerChanged(float Power, float MaxPower);

	FDelegateHandle PoweredHandle;
	
};
