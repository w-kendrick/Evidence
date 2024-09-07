// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBenchWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment.h"
#include "AttachmentWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "InventorySlot.h"

void UAttachmentBenchWidget::Enable()
{
	Super::Enable();

	UpdateAttachments();

	CurrentEquipment = Character->GetEquipped();
	if (CurrentEquipment)
	{
		CurrentEquipment->OnAttachmentsUpdated.AddUObject(this, &ThisClass::UpdateAttachments);
	}

	UInventoryManagerComponent* const InventoryComp = Character->GetInventoryComponent();
	InventoryComp->OnInventoryChanged.AddUObject(this, &ThisClass::UpdateInventory);
}

void UAttachmentBenchWidget::Disable()
{
	AttachmentBox->ClearChildren();
	InventoryBox->ClearChildren();

	Super::Disable();
}

void UAttachmentBenchWidget::UpdateAttachments()
{
	AttachmentBox->ClearChildren();

	Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Character)
	{
		CurrentEquipment = Character->GetEquipped();

		if (CurrentEquipment)
		{
			const TMap<EAttachmentType, AEquipmentAttachment*>& Attachments = CurrentEquipment->GetAttachments();

			for (const TPair<EAttachmentType, AEquipmentAttachment*>& Elem : Attachments)
			{
				UAttachmentWidget* const Widget = CreateWidget<UAttachmentWidget>(this, AttachmentWidgetClass);

				if (Widget)
				{
					Widget->SpawnInitialize(Elem.Key, CurrentEquipment);
					AttachmentBox->AddChild(Widget);
				}
			}
		}
	}
}

void UAttachmentBenchWidget::UpdateInventory(FEquipmentList EquipmentList)
{
	InventoryBox->ClearChildren();

	UInventoryManagerComponent* const InventoryComp = Character->GetInventoryComponent();

	if (InventoryComp)
	{
		const FEquipmentList& Inventory = EquipmentList;

		const uint8 Rows = FMath::CeilToInt(((float)INVENTORY_SIZE) / Columns);
		UHorizontalBox* CurrentRow = nullptr;

		for (uint8 i = 0; i < INVENTORY_SIZE; i++)
		{
			if (i % 2 == 0)
			{
				CurrentRow = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				InventoryBox->AddChild(CurrentRow);
			}

			AEquipment* const Equipment = Inventory[i].GetEquipment();
			UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(i, InventoryComp);
				CurrentRow->AddChild(NewSlot);
			}
		}
	}
}
