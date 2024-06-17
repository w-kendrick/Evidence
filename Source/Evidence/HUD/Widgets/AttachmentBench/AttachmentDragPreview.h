// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Enums/AttachmentType.h"
#include "AttachmentDragPreview.generated.h"

class UTextBlock;
class AEquipment;

UCLASS()
class EVIDENCE_API UAttachmentDragPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAttachmentType(const EAttachmentType NewType);
	void SetEquipped(AEquipment* const Equipment);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttachmentText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TypeText;

	EAttachmentType AttachmentType;

	UPROPERTY()
	AEquipment* Equipped;
	
};
