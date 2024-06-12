// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDragPreview.h"
#include "Components/TextBlock.h"

void UAttachmentDragPreview::NativeConstruct()
{
	Super::NativeConstruct();

	AttachmentText->SetText(FText::FromString(UEnum::GetValueAsString(AttachmentType)));
}

void UAttachmentDragPreview::SetAttachmentType(const EAttachmentType NewType)
{
	AttachmentType = NewType;
}
