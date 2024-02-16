// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ServerBrowser.h"
#include "HostMenu.h"

void UMenu::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
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

}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}

	return true;
}

void UMenu::HostButtonClicked()
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

void UMenu::JoinButtonClicked()
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
