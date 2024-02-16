// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerListRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MultiplayerSessionsSubsystem.h"
#include "ServerBrowser.h"
#include "OnlineSubsystem.h"

void UServerListRow::NativeConstruct()
{
	Super::NativeConstruct();

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	if (NameText)
	{
		FString Name = SearchResult.Session.OwningUserName;
		NameText->SetText(FText::FromString(Name));
	}

	if (MatchText)
	{
		FString MatchType;
		SearchResult.Session.SessionSettings.Get(FName("MatchType"), MatchType);
		MatchText->SetText(FText::FromString(MatchType));
	}

	if (CountText)
	{
		int MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
		int CurrentPlayers = MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
		FString Count = FString::FromInt(CurrentPlayers) + "/" + FString::FromInt(MaxPlayers);
		CountText->SetText(FText::FromString(Count));
	}

	if (PingText)
	{
		int Ping = SearchResult.PingInMs;
		PingText->SetText(FText::FromString(FString::FromInt(Ping)));
	}


	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
	}
}

void UServerListRow::SpawnInitialize(FOnlineSessionSearchResult Result, UServerBrowser* Browser)
{
	SearchResult = Result;
	OwningBrowser = Browser;
}

void UServerListRow::JoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		if (OwningBrowser)
		{
			OwningBrowser->RemoveFromParent();
		}
		MultiplayerSessionsSubsystem->JoinSession(SearchResult);
	}
}

void UServerListRow::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			if (SessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
			{
				APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
				if (PlayerController)
				{
					RemoveFromParent();
					PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(
							-1,
							15.f,
							FColor::Green,
							FString::Printf(TEXT("Joined"))
						);
						GEngine->AddOnScreenDebugMessage(
							-1,
							15.f,
							FColor::Green,
							Address
						);
					}
				}
			}
		}
	}
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
}