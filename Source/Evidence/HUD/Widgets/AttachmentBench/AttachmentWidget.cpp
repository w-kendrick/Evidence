// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentWidget.h"
#include "Components/TextBlock.h"

void UAttachmentWidget::SpawnInitialize(const EAttachmentType Type, UAttachmentComponent* const Comp)
{
	AttachmentType = Type;
	Attachment = Comp;
}

void UAttachmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AttachmentText)
	{
		AttachmentText->SetText(FText::FromString(UEnum::GetValueAsString(AttachmentType)));
	}
}
