// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerWidget.h"
#include "Evidence/Hub/Locker.h"
#include "Kismet/GameplayStatics.h"
#include "LockerSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h"

void ULockerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeSlots();

	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	if (Locker)
	{
		Locker->OnLockerStorageChanged.AddUObject(this, &ThisClass::OnLockerStorageChanged);
	}
}

void ULockerWidget::LeaveEvent()
{
	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	if (Locker)
	{
		Locker->Relinquish();
	}

	Super::LeaveEvent();
}

void ULockerWidget::InitializeSlots()
{
	UHorizontalBox* CurrentRow = nullptr;

	for (uint8 Index = 0; Index < ALocker::STORAGE_CAPACITY; Index++)
	{
		if (Index % 8 == 0)
		{
			CurrentRow = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
			LockerRows->AddChild(CurrentRow);
		}
		ULockerSlotWidget* const LockerSlot = CreateWidget<ULockerSlotWidget>(this, SlotClass);
		LockerSlot->SetIndex(Index);
		CurrentRow->AddChild(LockerSlot);
		LockerSlots.Add(LockerSlot);
	}
}

void ULockerWidget::OnLockerStorageChanged(const FEquipmentList& EquipmentList)
{
	for (uint8 Index = 0; Index < ALocker::STORAGE_CAPACITY; Index++)
	{
		const AEquipment* const Equipment = EquipmentList[Index].GetEquipment();
		LockerSlots[Index]->UpdateSlot(Equipment);
	}
}
