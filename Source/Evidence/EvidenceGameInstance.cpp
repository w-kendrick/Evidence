// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameInstance.h"

UEvidenceGameInstance::UEvidenceGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SlotName = FString("Save1");
}

void UEvidenceGameInstance::SetSlotName(const FString& Name)
{
	SlotName = Name;
}
