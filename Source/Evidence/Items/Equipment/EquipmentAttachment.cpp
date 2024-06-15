// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAttachment.h"

AEquipmentAttachment::AEquipmentAttachment()
{
}

void AEquipmentAttachment::AttachTo(AEquipment* const Equipment)
{
	for (const TSubclassOf<UEIGameplayAbility>& Ability : AttachmentAbilities)
	{
		FGameplayAbilitySpecHandle Handle = Equipment->AddAttachmentAbility(Ability);
		GrantedAttachmentAbilities.Add(Handle);
	}

	OwningEquipment = Equipment;
}

void AEquipmentAttachment::DetachFrom()
{
	for (const FGameplayAbilitySpecHandle& Handle : GrantedAttachmentAbilities)
	{
		OwningEquipment->RemoveAttachmentAbility(Handle);
	}

	OwningEquipment = nullptr;
}
