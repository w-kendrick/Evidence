// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentComponent.h"
#include "Evidence/Items/Equipment.h"

UAttachmentComponent::UAttachmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UAttachmentComponent::AttachTo(AEquipment* const Equipment)
{
	for (const TSubclassOf<UEIGameplayAbility>& Ability : Abilities)
	{
		Equipment->AddAttachmentAbility(Ability);
	}

	OwningEquipment = Equipment;
}
