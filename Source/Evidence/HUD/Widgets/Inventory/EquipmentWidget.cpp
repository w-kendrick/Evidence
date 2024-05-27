// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Items/QuantityEquipment.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
	SlotButton->OnHovered.AddDynamic(this, &ThisClass::OnHover);
	SlotButton->OnUnhovered.AddDynamic(this, &ThisClass::OnUnhover);

	Display();
}

void UEquipmentWidget::SpawnInitialize(UInventoryComponent* Comp, AEquipment* NewEquipment)
{
	InventoryComp = Comp;
	Equipment = NewEquipment;
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
		InventoryComp->TryDropEquipped();
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
		if (Equipment)
		{
			ObjectName->SetText(FText::FromString(Equipment->GetEquipmentName()));
		}
		else
		{
			ObjectName->SetText(FText::FromString(FString(TEXT("Empty"))));
		}

		const AQuantityEquipment* const QEquipment = Cast<AQuantityEquipment>(Equipment);
		if (QEquipment)
		{
			ObjectCount->SetText(FText::FromString(FString::FromInt(QEquipment->GetQuantity())));
		}
		else
		{
			ObjectCount->SetText(FText::FromString(""));
		}
	}
}
