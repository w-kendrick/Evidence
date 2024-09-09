// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Enums/AttachmentType.h"
#include "EquipmentAttachment.generated.h"

class UAbilitySet;

UCLASS()
class EVIDENCE_API AEquipmentAttachment : public AEquipment
{
	GENERATED_BODY()

public:
	AEquipmentAttachment();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;

	void AttachTo(AEquipment* const Equipment);
	void DetachFrom();

	bool CanAttach(const EAttachmentType Type, const TSubclassOf<AEquipment>& Class) const;

	FORCEINLINE EAttachmentType GetAttachmentType() const { return AttachmentType; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EAttachmentType AttachmentType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<const UAbilitySet> AttachmentAbilitySet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEquipment> PermittedClass;

	UPROPERTY()
	AEquipment* OwningEquipment;
};
