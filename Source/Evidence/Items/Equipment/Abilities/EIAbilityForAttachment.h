// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "Evidence/Enums/AttachmentType.h"
#include "EIAbilityForAttachment.generated.h"

class AEquipmentAttachment;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UEIAbilityForAttachment : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	EAttachmentType AttachmentType;

	AEquipmentAttachment* GetAttachment(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;
};
