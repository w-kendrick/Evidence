// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/DisableInputWidget.h"
#include "AttachmentBenchWidget.generated.h"

class AEquipment;
class AEvidenceCharacter;
class UAttachmentWidget;
class UVerticalBox;

UCLASS()
class EVIDENCE_API UAttachmentBenchWidget : public UDisableInputWidget
{
	GENERATED_BODY()
	
public:
	virtual void Enable() override;
	virtual void Disable() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* AttachmentBox;

	UPROPERTY()
	AEquipment* CurrentEquipment;

	UPROPERTY()
	AEvidenceCharacter* Character;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttachmentWidget> AttachmentWidgetClass;
};