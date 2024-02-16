// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerBrowser.h"
#include "MultiplayerSessionsSubsystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ServerListRow.h"
#include "Components/ScrollBox.h"
#include "Menu.h"
#include "Components/CircularThrobber.h"

void UServerBrowser::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UServerBrowser::BackButtonClicked);
	}
	if (FindButton)
	{
		FindButton->OnClicked.AddDynamic(this, &UServerBrowser::FindButtonClicked);
	}

	if (LoadSymbol)
	{
		LoadSymbol->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SearchStatusText)
	{
		SearchStatusText->SetText(FText::FromString(FString("Search")));
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
	}
}

void UServerBrowser::BackButtonClicked()
{
	if (MenuClass)
	{
		UMenu* Menu = CreateWidget<UMenu>(this, MenuClass);
		if (Menu)
		{
			if (BackButton)
			{
				BackButton->SetIsEnabled(false);
			}
			Menu->AddToViewport();
			Menu->MenuSetup(4, FString("FreeForAll"), FString("/Game/Rush/Maps/Lobby"));
			RemoveFromParent();
		}
	}
}

void UServerBrowser::FindButtonClicked()
{
	if (BrowserBox)
	{
		BrowserBox->ClearChildren();
	}
	StartSearch();
	MultiplayerSessionsSubsystem->FindSessions(10000);
	if (FindText)
	{
		FindText->SetText(FText::FromString(FString("Refresh")));
	}
}

void UServerBrowser::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessul)
{
	EndSearch();

	if (MultiplayerSessionsSubsystem == nullptr)
	{
		return;
	}

	for (auto Result : SessionResults)
	{
		UServerListRow* Row = CreateWidget<UServerListRow>(this, RowClass);
		Row->SpawnInitialize(Result, this);
		if (BrowserBox && Row)
		{
			BrowserBox->AddChild(Row);
		}
	}
}

void UServerBrowser::StartSearch()
{
	if (BackButton)
	{
		BackButton->SetIsEnabled(false);
	}
	if (FindButton)
	{
		FindButton->SetIsEnabled(false);
	}
	if (SearchStatusText)
	{
		SearchStatusText->SetText(FText::FromString(FString("Searching...")));
	}
	if (LoadSymbol)
	{
		LoadSymbol->SetVisibility(ESlateVisibility::Visible);
	}
}

void UServerBrowser::EndSearch()
{
	if (BackButton)
	{
		BackButton->SetIsEnabled(true);
	}
	if (FindButton)
	{
		FindButton->SetIsEnabled(true);
	}
	if (SearchStatusText)
	{
		SearchStatusText->SetText(FText::FromString(FString("Complete")));
	}
	if (LoadSymbol)
	{
		LoadSymbol->SetVisibility(ESlateVisibility::Hidden);
	}
}