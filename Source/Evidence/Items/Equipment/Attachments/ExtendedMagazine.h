// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"
#include "ExtendedMagazine.generated.h"

/**
	Increases the size of the magazine of guns
*/
UCLASS()
class EVIDENCE_API AExtendedMagazine : public AEquipmentAttachment
{
	GENERATED_BODY()

public:
	AExtendedMagazine();

	/**
		Returns the size of the extended magazine

		@return Size of the extended magazine
	*/
	FORCEINLINE uint8 GetExtendedMagazineSize() const { return ExtendedMagazineSize; }

protected:
	UPROPERTY(EditDefaultsOnly)
	uint8 ExtendedMagazineSize;
};
