// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "AttachmentDragPreview.h"
#include "AttachmentDragWidget.h"
#include "InventoryDragWidget.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "InventoryDragPreview.h"

void UAttachmentWidget::SpawnInitialize(const EAttachmentType Type, AEquipment* const Equipment)
{
	AttachmentType = Type;
	Equipped = Equipment;
}

void UAttachmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TypeText->SetText(FText::FromString(UEnum::GetValueAsString(AttachmentType)));
	TypeText->SetColorAndOpacity(FSlateColor());

	if (Equipped)
	{
		AEquipmentAttachment* const Attachment = Equipped->GetAttachment(AttachmentType);

		if (Attachment)
		{
			AttachmentText->SetText(FText::FromString(Attachment->GetEquipmentName()));
		}
		else
		{
			AttachmentText->SetText(FText::FromString(TEXT("Empty")));
		}
	}
	else
	{
		AttachmentText->SetText(FText::FromString(TEXT("")));
	}
}

FReply UAttachmentWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton) && Equipped && Equipped->GetAttachment(AttachmentType))
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
	DragPreview->SetEquipped(Equipped);
	DragPreview->SetColour(FColor::Black);

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

	const uint8 Index = DragWidget->GetIndex();
	
	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;
	Data->HitResult.ElementIndex = static_cast<uint8>(AttachmentType);

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPlayerPawn(), FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.AttachmentSwap"))), Payload);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::FromInt(Index) + FString(TEXT(" dragged onto ")) + UEnum::GetValueAsString(AttachmentType));

	return true;
}

void UAttachmentWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragWidget* DragWidget = Cast<UInventoryDragWidget>(InOperation);

	if (!DragWidget)
	{
		return;
	}

	const UInventoryManagerComponent* const InventoryComponent = DragWidget->GetInventoryComponent();
	const uint8 Index = DragWidget->GetIndex();

	AEquipmentAttachment* const NewAttachment = Cast<AEquipmentAttachment>(InventoryComponent->GetEquipmentAtIndex(Index));

	if (NewAttachment)
	{
		UInventoryDragPreview* const Preview = Cast<UInventoryDragPreview>(DragWidget->DefaultDragVisual);

		if (NewAttachment->CanAttach(AttachmentType, Equipped->GetClass()))
		{
			Preview->SetColour(FColor::Green);
		}
		else
		{
			Preview->SetColour(FColor::Red);
		}
	}
}

void UAttachmentWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragWidget* DragWidget = Cast<UInventoryDragWidget>(InOperation);

	if (!DragWidget)
	{
		return;
	}

	UInventoryDragPreview* const Preview = Cast<UInventoryDragPreview>(DragWidget->DefaultDragVisual);
	Preview->SetColour(FColor::Black);
}
