// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalShopMenu.generated.h"

class UTerminalShopItemWidget;
class UVerticalBox;

UCLASS()
class EVIDENCE_API UTerminalShopMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTerminalShopItemWidget> ItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Box;
	
};
