// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceAssetManager.h"
#include "AbilitySystemGlobals.h"

void UEvidenceAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
