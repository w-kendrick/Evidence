// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AdvancedGameplayAbility.h"
#include "EIAttachmentSwap.generated.h"

UCLASS()
class EVIDENCE_API UEIAttachmentSwap : public UAdvancedGameplayAbility
{
	GENERATED_BODY()

public:
	UEIAttachmentSwap();

	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
};
