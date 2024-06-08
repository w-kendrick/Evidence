// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/DisableInputWidget.h"
#include "AttachmentBenchWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UAttachmentBenchWidget : public UDisableInputWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	AEquipment* CurrentEquipment;
};
