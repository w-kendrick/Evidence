// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttachmentComponent.generated.h"

class UEIGameplayAbility;
class AEquipment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UAttachmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttachmentComponent();

	void AttachTo(AEquipment* const Equipment);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UEIGameplayAbility>> Abilities;

	UPROPERTY()
	AEquipment* OwningEquipment;
	
};
