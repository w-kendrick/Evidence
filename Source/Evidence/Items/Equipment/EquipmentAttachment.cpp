// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAttachment.h"

AEquipmentAttachment::AEquipmentAttachment()
{
	EquipmentName = FString(TEXT("Attachment"));
}

bool AEquipmentAttachment::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return Super::IsAvailableForInteraction_Implementation(InteractionComponent) && !OwningEquipment;
}

void AEquipmentAttachment::AttachTo(AEquipment* const Equipment)
{
	for (const TSubclassOf<UEIGameplayAbility>& Ability : AttachmentAbilities)
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			FGameplayAbilitySpecHandle Handle = Equipment->AddAttachmentAbility(Ability);
			const FGrantedAbility Granted = { Ability, Handle };
			GrantedAttachmentAbilities.Add(Granted);
		}
	}

	OwningEquipment = Equipment;

	const FAttachmentTransformRules Rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
	AttachToActor(OwningEquipment, Rule);
}

void AEquipmentAttachment::DetachFrom()
{
	for (const FGrantedAbility& Granted : GrantedAttachmentAbilities)
	{
		OwningEquipment->RemoveAttachmentAbility(Granted.AbilityHandle, Granted.AbilityClass);
	}

	OwningEquipment = nullptr;

	const FDetachmentTransformRules Rule = FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
	DetachFromActor(Rule);
}

bool AEquipmentAttachment::CanAttach(const EAttachmentType Type, const TSubclassOf<AEquipment>& Class) const
{
	return GetAttachmentType() == Type && Class == PermittedClass;
}
