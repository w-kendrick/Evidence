// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSwapAbility.h"
#include "Evidence/Character/BaseCharacter.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Hub/Locker.h"
#include "Kismet/GameplayStatics.h"

void ULockerSwapAbility::Activate(const FGameplayEventData& EventData)
{
	FGameplayAbilityTargetData* const Data = EventData.TargetData.Data[0].Get();

	const uint8 InventoryIndex = Data->GetHitResult()->FaceIndex;
	const uint8 LockerIndex = Data->GetHitResult()->ElementIndex;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Swap Locker: ") + FString::FromInt(LockerIndex) + FString(" / Inventory: ") + FString::FromInt(InventoryIndex));

	ABaseCharacter* const Char = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());
	if (!Char)
	{
		return;
	}

	UInventoryManagerComponent* const InventoryComponent = Char->GetInventoryComponent();
	if (!InventoryComponent)
	{
		return;
	}

	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));
	if (!Locker)
	{
		return;
	}

	AEquipment* const InventoryEquipment = InventoryComponent->GetEquipmentAtIndex(InventoryIndex);
	AEquipment* const LockerEquipment = Locker->GetEquipmentAtIndex(LockerIndex);

	InventoryComponent->Drop(InventoryIndex);
	Locker->Remove(LockerIndex);

	InventoryComponent->Pickup(LockerEquipment, InventoryIndex);
	Locker->SetEquipmentAtIndex(InventoryEquipment, LockerIndex);
}
