// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Evidence/Enums/EquipmentID.h"
#include "EnumLibrary.generated.h"

UCLASS()
class EVIDENCE_API UEnumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString To_String(const EEquipmentID ID);
	
};
