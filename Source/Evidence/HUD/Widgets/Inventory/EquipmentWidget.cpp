// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Evidence/Character/Components/InventoryComponent.h"
//#include "AlienEvidence/FunctionLibraries/EnumLibrary.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
	SlotButton->OnHovered.AddDynamic(this, &ThisClass::OnHover);
	SlotButton->OnUnhovered.AddDynamic(this, &ThisClass::OnUnhover);

	Display();
}

void UEquipmentWidget::SpawnInitialize(UInventoryComponent* Comp, const EEquipmentID Object)
{
	InventoryComp = Comp;
	Slot = Object;
}

FReply UEquipmentWidget::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(RightMouse))
	{
		if (isCursorOverButton)
		{
			ButtonRightClicked();
		}

		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void UEquipmentWidget::OnClicked()
{
	ButtonLeftClicked();
}

void UEquipmentWidget::ButtonLeftClicked()
{
	
}

void UEquipmentWidget::ButtonRightClicked()
{
	if (InventoryComp)
	{
		//InventoryComp->DropEquippedFromInventory();
	}
}

void UEquipmentWidget::OnHover()
{
	isCursorOverButton = true;
}

void UEquipmentWidget::OnUnhover()
{
	isCursorOverButton = false;
}

void UEquipmentWidget::Display()
{
	if (ObjectName)
	{
		//FString Name = UEnumLibrary::To_String(Slot);
		//ObjectName->SetText(FText::FromString(Name));
	}
}
