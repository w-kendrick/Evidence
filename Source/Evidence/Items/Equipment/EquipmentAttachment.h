// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Enums/AttachmentType.h"
#include "EquipmentAttachment.generated.h"

class UAttachmentComponent;

UCLASS()
class EVIDENCE_API AEquipmentAttachment : public AEquipment
{
	GENERATED_BODY()

public:
	AEquipmentAttachment();

	FORCEINLINE TSubclassOf<UAttachmentComponent> GetComponentClass() const { return ComponentClass; }
	FORCEINLINE EAttachmentType GetType() const { return Type; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttachmentComponent> ComponentClass;

	UPROPERTY(EditDefaultsOnly)
	EAttachmentType Type;
};
