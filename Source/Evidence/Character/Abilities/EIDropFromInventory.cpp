// Fill out your copyright notice in the Description page of Project Settings.


#include "EIDropFromInventory.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"

UEIDropFromInventory::UEIDropFromInventory()
{
	AbilityInputID = EAbilityInputID::None;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.DropFromInventory"))));
}

void UEIDropFromInventory::Activate(const FGameplayEventData& EventData)
{
	FGameplayAbilityTargetData* const Data = EventData.TargetData.Data[0].Get();
	const uint8 Index = Data->GetHitResult()->FaceIndex;

	AEvidenceCharacter* const Char = Cast<AEvidenceCharacter>(GetAvatarActorFromActorInfo());

	if (!Char)
	{
		return;
	}

	UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();

	if (!InventoryComponent)
	{
		return;
	}

	InventoryComponent->Drop(Index);
}
