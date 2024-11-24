// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFunctionLibrary.generated.h"

class UGameplayEffect;
class AEquipment;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UTestFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void StartSetupPeriod(UWorld* World);
	static void KillPlayer(ACharacter* Character, const TSubclassOf<UGameplayEffect>& KillPlayerEffectClass);
	static void ApplyGameplayEffect(ACharacter* Character, const TSubclassOf<UGameplayEffect>& EffectClass);

	static AEquipment* SpawnEquipment(UWorld* World, const TSubclassOf<AEquipment>& EquipmentClass, const FVector& Location);
	
};
