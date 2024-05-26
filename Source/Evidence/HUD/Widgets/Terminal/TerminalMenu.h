// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalMenu.generated.h"

class UButton;
class UTerminalShopMenu;

UCLASS()
class EVIDENCE_API UTerminalMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void Enable();
	void Disable();

protected:
	void NativeConstruct() override;
	void LeaveTerminal();

	UPROPERTY(meta = (BindWidget))
	UButton* ShopButton;

	UFUNCTION()
	void OnShopClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTerminalShopMenu> ShopMenuClass;

	UTerminalShopMenu* ShopMenu;

private:
	FTimerHandle LeaveHandle;
	
};
