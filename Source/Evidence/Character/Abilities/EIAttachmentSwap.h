// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Character/Abilities/EIGameplayAbility.h"
#include "EIAttachmentSwap.generated.h"

UCLASS()
class EVIDENCE_API UEIAttachmentSwap : public UEIGameplayAbility
{
	GENERATED_BODY()

public:
	UEIAttachmentSwap();

	UFUNCTION(BlueprintCallable)
	void Activate(const FGameplayEventData& EventData);
};
