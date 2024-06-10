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
			const TMap<EAttachmentType, UAttachmentComponent*>& Attachments = CurrentEquipment->GetAttachments();

			for (const TPair<EAttachmentType, UAttachmentComponent*>& Elem : Attachments)
			{
				UAttachmentWidget* const Widget = CreateWidget<UAttachmentWidget>(this, AttachmentWidgetClass);

				if (Widget)
				{
					Widget->SpawnInitialize(Elem.Key, Elem.Value);
					AttachmentBox->AddChild(Widget);
				}
			}
		}
	}

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
				//NewSlot->SpawnInitialize(InventoryComp, Equipment, i);
				CurrentRow->AddChild(NewSlot);
			}
		}
	}
}

void UAttachmentBenchWidget::Disable()
{
	AttachmentBox->ClearChildren();
	InventoryBox->ClearChildren();

	Super::Disable();
}
