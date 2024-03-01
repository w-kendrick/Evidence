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

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}

	Update();
}

void UInventoryWidget::NativeDestruct()
{
	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	Super::NativeDestruct();
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

		TArray<EEquipmentID> Inventory = InventoryComp->GetInventory();
		EEquipmentID EquippedType = InventoryComp->GetEquippedType();

		const uint8 Columns = FMath::CeilToInt(((float)Inventory.Num()) / Rows);

		UHorizontalBox* CurrentRow = nullptr;
		for (uint8 i = 0; i < Inventory.Num(); i++)
		{
			if (i % Columns == 0)
			{
				CurrentRow = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
				InventoryBox->AddChild(CurrentRow);
			}

			const EEquipmentID Object = Inventory[i];
			UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, SlotClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(InventoryComp, Object, i);
				CurrentRow->AddChild(NewSlot);
			}
			InventorySlots.Add(NewSlot);
		}

		if (EquippedBox)
		{
			UEquipmentWidget* NewSlot = CreateWidget<UEquipmentWidget>(this, EquippedClass);
			if (NewSlot)
			{
				NewSlot->SpawnInitialize(InventoryComp, EquippedType);
				EquippedBox->AddChild(NewSlot);
			}
		}
	}
}