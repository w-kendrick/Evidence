// Fill out your copyright notice in the Description page of Project Settings.


#include "EIAttachmentSwap.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Enums/AttachmentType.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"

UEIAttachmentSwap::UEIAttachmentSwap()
{
	AbilityInputID = EAbilityInputID::None;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.AttachmentSwap"))));
}

void UEIAttachmentSwap::Activate(const FGameplayEventData& EventData)
{
	FGameplayAbilityTargetData* const Data = EventData.TargetData.Data[0].Get();
	const uint8 Index = Data->GetHitResult()->FaceIndex;
	const EAttachmentType AttachmentType = static_cast<EAttachmentType>(Data->GetHitResult()->ElementIndex);

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

	AEquipment* const Equipped = InventoryComponent->GetEquipped();

	if (!Equipped)
	{
		return;
	}

	AEquipmentAttachment* const NewAttachment = Cast<AEquipmentAttachment>(InventoryComponent->GetEquipmentAtIndex(Index));
	AEquipmentAttachment* const CurrentAttachment = Equipped->GetAttachment(AttachmentType);

	if (NewAttachment && !NewAttachment->CanAttach(AttachmentType, Equipped->GetClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Swap failed due to mismatch");
		return;
	}

	InventoryComponent->Drop(Index);
	Equipped->RemoveAttachment(AttachmentType);
	InventoryComponent->Pickup(CurrentAttachment, Index);
	Equipped->AddAttachment(NewAttachment, AttachmentType);
}
