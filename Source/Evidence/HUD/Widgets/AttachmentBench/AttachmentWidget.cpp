// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "AttachmentDragPreview.h"
#include "AttachmentDragWidget.h"
#include "InventoryDragWidget.h"

void UAttachmentWidget::SpawnInitialize(const EAttachmentType Type, UAttachmentComponent* const Comp)
{
	AttachmentType = Type;
	Attachment = Comp;
}

void UAttachmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AttachmentText)
	{
		AttachmentText->SetText(FText::FromString(UEnum::GetValueAsString(AttachmentType)));
	}
}

FReply UAttachmentWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}

	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UAttachmentWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UAttachmentDragPreview* DragPreview = CreateWidget<UAttachmentDragPreview>(this, DragPreviewClass);
	DragPreview->SetAttachmentType(AttachmentType);

	UAttachmentDragWidget* DragWidget = Cast<UAttachmentDragWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragWidgetClass));
	DragWidget->DefaultDragVisual = DragPreview;
	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->SetAttachmentType(AttachmentType);

	OutOperation = DragWidget;
}

bool UAttachmentWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragWidget* DragWidget = Cast<UInventoryDragWidget>(InOperation);

	if (!DragWidget)
	{
		return false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::FromInt(DragWidget->GetIndex()) + FString(TEXT(" dragged onto ")) + UEnum::GetValueAsString(AttachmentType));

	return true;
}
