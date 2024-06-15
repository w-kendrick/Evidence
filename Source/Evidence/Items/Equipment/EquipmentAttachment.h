// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Enums/AttachmentType.h"
#include "EquipmentAttachment.generated.h"

class UEIGameplayAbility;

UCLASS()
class EVIDENCE_API AEquipmentAttachment : public AEquipment
{
	GENERATED_BODY()

public:
	AEquipmentAttachment();

	void AttachTo(AEquipment* const Equipment);
	void DetachFrom();

	FORCEINLINE EAttachmentType GetType() const { return Type; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EAttachmentType Type;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UEIGameplayAbility>> AttachmentAbilities;

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAttachmentAbilities;

	UPROPERTY()
	AEquipment* OwningEquipment;
};
