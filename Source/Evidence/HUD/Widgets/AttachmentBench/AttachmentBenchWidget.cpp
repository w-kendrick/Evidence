// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBenchWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment.h"
#include "AttachmentWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "InventorySlot.h"

void UAttachmentBenchWidget::Enable()
{
	Super::Enable();

	Character = Cast<AEvidenceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

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

	UpdateInventory();

	UInventoryComponent* const InventoryComp = Character->GetInventoryComponent();
	InventoryComp->InventoryChanged.AddUObject(this, &ThisClass::UpdateInventory);
}

void UAttachmentBenchWidget::Disable()
{
	AttachmentBox->ClearChildren();
	InventoryBox->ClearChildren();

	Super::Disable();
}

void UAttachmentBenchWidget::UpdateInventory()
{
	InventoryBox->ClearChildren();

	UInventoryComponent* const InventoryComp = Character->GetInventoryComponent();

	if (InventoryComp)
	{
		TArray<AEquipment*> Inventory = InventoryComp->GetInventory();

		const uint8 Rows = FMath::CeilToInt(((float)Inventory.Num()) / Columns);
		UHorizontalBox* CurrentRow = nullptr;

		for (uint8 i = 0; i < Inventory.Num(); i++)
		{
			if (i % 2 == 0)
			{
				CurrentRow = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				InventoryBox->AddChild(CurrentRow);
			}

			AEquipment* Equipment = Inventory[i];
			UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(i, InventoryComp);
				CurrentRow->AddChild(NewSlot);
			}
		}
	}
}
