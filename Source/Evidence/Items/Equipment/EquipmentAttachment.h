// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "EquipmentAttachment.generated.h"

class UAttachmentComponent;

UCLASS()
class EVIDENCE_API AEquipmentAttachment : public AEquipment
{
	GENERATED_BODY()

public:
	AEquipmentAttachment();

	FORCEINLINE TSubclassOf<UAttachmentComponent> GetComponentClass() const { return ComponentClass; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttachmentComponent> ComponentClass;
};
