// Fill out your copyright notice in the Description page of Project Settings.


#include "EIAbilityForAttachment.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"

AEquipmentAttachment* UEIAbilityForAttachment::GetAttachment(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const
{
	const AEquipment* const Equipment = Cast<AEquipment>(GetSourceObject(Handle, ActorInfo));

	if (!Equipment)
	{
		return nullptr;
	}

	AEquipmentAttachment* const Attachment = Equipment->GetAttachment(AttachmentType);

	return Attachment;
}
