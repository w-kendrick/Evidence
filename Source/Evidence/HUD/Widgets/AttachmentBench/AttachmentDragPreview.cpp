// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDragPreview.h"
#include "Components/TextBlock.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"

void UAttachmentDragPreview::NativeConstruct()
{
	Super::NativeConstruct();

	TypeText->SetText(FText::FromString(UEnum::GetValueAsString(AttachmentType)));

	if (Equipped)
	{
		AEquipmentAttachment* const Attachment = Equipped->GetAttachment(AttachmentType);

		if (Attachment)
		{
			AttachmentText->SetText(FText::FromString(Attachment->GetEquipmentName()));
		}
		else
		{
			AttachmentText->SetText(FText::FromString(TEXT("Empty")));
		}
	}
	else
	{
		AttachmentText->SetText(FText::FromString(TEXT("")));
	}
}

void UAttachmentDragPreview::SetAttachmentType(const EAttachmentType NewType)
{
	AttachmentType = NewType;
}

void UAttachmentDragPreview::SetEquipped(AEquipment* const Equipment)
{
	Equipped = Equipment;
}

void UAttachmentDragPreview::SetColour(const FColor& Colour)
{
	AttachmentText->SetColorAndOpacity(FSlateColor(Colour));
}
