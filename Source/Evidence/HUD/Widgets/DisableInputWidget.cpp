// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableInputWidget.h"
#include "Components/Button.h"

void UDisableInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseClicked);
	}
}

void UDisableInputWidget::LeaveEvent()
{
	Disable();
}

void UDisableInputWidget::Enable()
{
	APlayerController* const PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
	}

	SetVisibility(ESlateVisibility::Visible);
	isActive = true;
}

void UDisableInputWidget::Disable()
{
	APlayerController* const PC = GetOwningPlayer();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

	SetVisibility(ESlateVisibility::Hidden);
	isActive = false;
}

void UDisableInputWidget::OnCloseClicked()
{
	LeaveEvent();
}

FReply UDisableInputWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "on key down");
	if (InKeyEvent.GetKey() == EscapeKey)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "escape");
		if (isActive)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "isactive");
			LeaveEvent();
		}
	}

	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}