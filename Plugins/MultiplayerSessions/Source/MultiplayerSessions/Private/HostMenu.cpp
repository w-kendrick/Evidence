// Fill out your copyright notice in the Description page of Project Settings.


#include "HostMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "MultiplayerSessionsSubsystem.h"
#include "Menu.h"

void UHostMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UHostMenu::BackButtonClicked);
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UHostMenu::HostButtonClicked);
	}

	if (PlayerSlider)
	{
		PlayerSlider->OnValueChanged.AddDynamic(this, &UHostMenu::PlayerSliderChanged);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

void UHostMenu::BackButtonClicked()
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
		}
		RemoveFromParent();
	}
}

void UHostMenu::HostButtonClicked()
{
	if (HostButton)
	{
		HostButton->SetIsEnabled(false);
	}
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(MaxPlayerCount, FString("Lobby"));
	}

}

void UHostMenu::PlayerSliderChanged(float Value)
{
	MaxPlayerCount = FMath::TruncToInt(FMath::Clamp(Value, 0.0f, 16.0f));
	CountText->SetText(FText::FromString(FString::FromInt(MaxPlayerCount)));
}

void UHostMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Maps/Lobby?listen");
		}
	}
	else
	{
		HostButton->SetIsEnabled(true);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Session failed to be created, please try again."))
			);
		}
	}
}