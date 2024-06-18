// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventoryDragWidget.h"
#include "AttachmentDragWidget.h"
#include "InventoryDragPreview.h"
#include "Components/TextBlock.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "Evidence/Items/Equipment/EquipmentAttachment.h"
#include "AttachmentDragPreview.h"

void UInventorySlot::SpawnInitialize(const uint8 Index, UInventoryComponent* Comp)
{
	InventoryIndex = Index;
	InventoryComponent = Comp;

	Update();
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Update();
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, LeftMouseButton).NativeReply;
	}

	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UInventoryDragPreview* DragPreview = CreateWidget<UInventoryDragPreview>(this, DragPreviewClass);
	DragPreview->SetIndex(InventoryIndex);
	DragPreview->SetInventoryComponent(InventoryComponent);
	DragPreview->SetColour(FColor::Black);

	UInventoryDragWidget* DragWidget = Cast<UInventoryDragWidget>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragWidgetClass));
	DragWidget->DefaultDragVisual = DragPreview;
	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->SpawnInitialize(InventoryIndex, InventoryComponent);

	OutOperation = DragWidget;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UAttachmentDragWidget* DragWidget = Cast<UAttachmentDragWidget>(InOperation);

	if (!DragWidget)
	{
		return false;
	}

	const EAttachmentType AttachmentType = DragWidget->GetAttachmentType();

	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = InventoryIndex;
	Data->HitResult.ElementIndex = static_cast<uint8>(AttachmentType);

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPlayerPawn(), FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.AttachmentSwap"))), Payload);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, UEnum::GetValueAsString(DragWidget->GetAttachmentType()) + FString(TEXT(" dragged onto ")) + FString::FromInt(InventoryIndex));

	return true;
}

void UInventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UAttachmentDragWidget* DragWidget = Cast<UAttachmentDragWidget>(InOperation);

	if (!DragWidget)
	{
		return;
	}

	const EAttachmentType AttachmentType = DragWidget->GetAttachmentType();

	AEquipmentAttachment* const NewAttachment = Cast<AEquipmentAttachment>(InventoryComponent->GetEquipmentAtIndex(InventoryIndex));

	UAttachmentDragPreview* const Preview = Cast<UAttachmentDragPreview>(DragWidget->DefaultDragVisual);

	if (NewAttachment)
	{
		const EAttachmentType Type = NewAttachment->GetAttachmentType();

		if (Type == AttachmentType)
		{
			Preview->SetColour(FColor::Green);
		}
		else
		{
			Preview->SetColour(FColor::Red);
		}
	}
	else
	{
		Preview->SetColour(FColor::Red);
	}
}

void UInventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UAttachmentDragWidget* DragWidget = Cast<UAttachmentDragWidget>(InOperation);

	if (!DragWidget)
	{
		return;
	}

	UAttachmentDragPreview* const Preview = Cast<UAttachmentDragPreview>(DragWidget->DefaultDragVisual);
	Preview->SetColour(FColor::Black);
}

void UInventorySlot::Update()
{
	AEquipment* const Equipment = InventoryComponent->GetEquipmentAtIndex(InventoryIndex);

	if (Equipment)
	{
		SlotText->SetText(FText::FromString(Equipment->GetEquipmentName()));
	}
	else
	{
		SlotText->SetText(FText::FromString(TEXT("Empty")));
	}
}
