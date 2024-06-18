// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DisableInputWidget.generated.h"

class UButton;

UCLASS()
class EVIDENCE_API UDisableInputWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Enable();
	virtual void Disable();

protected:
	virtual void NativeConstruct() override;
	virtual void LeaveEvent();

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION()
	void OnCloseClicked();

	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY(EditDefaultsOnly)
	FKey EscapeKey;

private:
	bool isActive;
	
};
