// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/HUD/Widgets/DisableInputWidget.h"
#include "TerminalMenu.generated.h"

class UButton;
class UTerminalShopMenu;

UCLASS()
class EVIDENCE_API UTerminalMenu : public UDisableInputWidget
{
	GENERATED_BODY()

public:
	void Disable() override;

protected:
	void NativeConstruct() override;
	void LeaveEvent() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ShopButton;

	UFUNCTION()
	void OnShopClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTerminalShopMenu> ShopMenuClass;

	UTerminalShopMenu* ShopMenu;
	
};
