// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Enums/AttachmentType.h"
#include "AttachmentDragPreview.generated.h"

class UTextBlock;

UCLASS()
class EVIDENCE_API UAttachmentDragPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAttachmentType(const EAttachmentType NewType);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttachmentText;

	EAttachmentType AttachmentType;
	
};
