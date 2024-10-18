// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerMainMenu.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "HostMenu/HostMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MultiplayerSessions/Subsystems/MultiplayerSessionsSubsystem.h"
#include "ServerBrowser/ServerBrowser.h"

void UMultiplayerMainMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	const UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UMultiplayerMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
	}

	return true;
}

void UMultiplayerMainMenu::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMultiplayerMainMenu::MenuTearDown()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			const FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	RemoveFromParent();
}

void UMultiplayerMainMenu::HostButtonClicked()
{
	if (HostMenuClass)
	{
		UHostMenu* HostMenu = CreateWidget<UHostMenu>(this, HostMenuClass);
		if (HostMenu)
		{
			if (HostButton)
			{
				HostButton->SetIsEnabled(false);
			}
			HostMenu->AddToViewport();
			RemoveFromParent();
		}
	}
}

void UMultiplayerMainMenu::JoinButtonClicked()
{
	if (BrowserClass)
	{
		UServerBrowser* Browser = CreateWidget<UServerBrowser>(this, BrowserClass);
		if (Browser)
		{
			if (JoinButton)
			{
				JoinButton->SetIsEnabled(false);
			}
			Browser->AddToViewport();
			RemoveFromParent();
		}
	}
}

void UMultiplayerMainMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
