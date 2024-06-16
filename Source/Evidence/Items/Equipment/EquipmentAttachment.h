// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Enums/AttachmentType.h"
#include "Evidence/Structs/GrantedAbility.h"
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

	FORCEINLINE EAttachmentType GetAttachmentType() const { return AttachmentType; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EAttachmentType AttachmentType;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UEIGameplayAbility>> AttachmentAbilities;

	UPROPERTY()
	TArray<FGrantedAbility> GrantedAttachmentAbilities;

	UPROPERTY()
	AEquipment* OwningEquipment;
};
