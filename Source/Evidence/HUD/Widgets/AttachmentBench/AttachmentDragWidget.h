// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Evidence/Enums/AttachmentType.h"
#include "AttachmentDragWidget.generated.h"

UCLASS()
class EVIDENCE_API UAttachmentDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetAttachmentType(const EAttachmentType NewType);
	EAttachmentType GetAttachmentType() const;

protected:
	EAttachmentType AttachmentType;
	
};
