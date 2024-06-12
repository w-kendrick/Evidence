// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDragWidget.h"

void UAttachmentDragWidget::SetAttachmentType(const EAttachmentType NewType)
{
	AttachmentType = NewType;
}

EAttachmentType UAttachmentDragWidget::GetAttachmentType() const
{
	return AttachmentType;
}
