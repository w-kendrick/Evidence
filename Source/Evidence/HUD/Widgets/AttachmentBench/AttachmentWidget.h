// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Enums/AttachmentType.h"
#include "AttachmentWidget.generated.h"

class UAttachmentComponent;
class UTextBlock;

UCLASS()
class EVIDENCE_API UAttachmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const EAttachmentType Type, UAttachmentComponent* const Comp);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttachmentText;

private:
	EAttachmentType AttachmentType;

	UPROPERTY()
	UAttachmentComponent* Attachment;
	
};
