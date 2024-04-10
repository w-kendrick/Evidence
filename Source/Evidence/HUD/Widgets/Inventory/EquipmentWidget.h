// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SpawnInitialize(class UInventoryComponent* Comp, AEquipment* NewEquipment);
	void Display();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ObjectName;

	UPROPERTY(EditDefaultsOnly)
	FKey LeftMouse;

	UPROPERTY(EditDefaultsOnly)
	FKey RightMouse;

	UPROPERTY()
	AEquipment* Equipment;
	class UInventoryComponent* InventoryComp;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void ButtonLeftClicked();
	virtual void ButtonRightClicked();

private:
	UFUNCTION()
	void OnClicked();

	bool isCursorOverButton;

	UFUNCTION()
	void OnHover();

	UFUNCTION()
	void OnUnhover();
};
