// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Evidence/Enums/AttachmentType.h"
#include "AttachmentWidget.generated.h"

class AEquipment;
class UTextBlock;
class UAttachmentDragPreview;
class UAttachmentDragWidget;

UCLASS()
class EVIDENCE_API UAttachmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(const EAttachmentType Type, AEquipment* const Equipment);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttachmentText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TypeText;

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttachmentDragPreview> DragPreviewClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttachmentDragWidget> DragWidgetClass;

private:
	EAttachmentType AttachmentType;

	UPROPERTY()
	AEquipment* Equipped;
	
};
