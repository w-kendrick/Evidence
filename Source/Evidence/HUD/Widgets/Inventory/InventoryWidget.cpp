// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "EquipmentWidget.h"
#include "InventorySlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AEvidencePlayerCharacter* PlayerChar = Cast<AEvidencePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerChar)
	{
		PlayerChar->GetInventoryComponent()->InventoryChanged.AddUObject(this, &ThisClass::OnInventoryChanged);
		PlayerChar->GetInventoryComponent()->EquippedChanged.AddUObject(this, &ThisClass::OnEquippedChanged);
	}

	Update();
}

void UInventoryWidget::OnInventoryChanged()
{
	Update();
}

void UInventoryWidget::OnEquippedChanged(AEquipment* Current, AEquipment* Previous)
{
	Update();
}

void UInventoryWidget::SetInventoryComp(UInventoryComponent* Comp)
{
	InventoryComp = Comp;
	Update();
}

void UInventoryWidget::Update()
{
	if (InventoryComp)
	{
		InventoryBox->ClearChildren();
		EquippedBox->ClearChildren();

		TArray<AEquipment*> Inventory = InventoryComp->GetInventory();
		AEquipment* Equipped = InventoryComp->GetEquipped();

		const uint8 Columns = FMath::CeilToInt(((float)Inventory.Num()) / Rows);

		UHorizontalBox* CurrentRow = nullptr;
		for (uint8 i = 0; i < Inventory.Num(); i++)
		{
			if (i % Columns == 0)
			{
				CurrentRow = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				InventoryBox->AddChild(CurrentRow);
			}

			AEquipment* Equipment = Inventory[i];
			UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(InventoryComp, Equipment, i);
				CurrentRow->AddChild(NewSlot);
			}
			InventorySlots.Add(NewSlot);
		}

		if (EquippedBox)
		{
			UEquipmentWidget* NewSlot = CreateWidget<UEquipmentWidget>(this, EquippedClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(InventoryComp, Equipped);
				EquippedBox->AddChild(NewSlot);
			}
		}
	}
}