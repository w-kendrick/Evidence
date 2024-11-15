// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/DisableInputWidget.h"
#include "LockerWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVIDENCE_API ULockerWidget : public UDisableInputWidget
{
	GENERATED_BODY()

protected:
	void LeaveEvent() override;
	
};