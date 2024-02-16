// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

void ULobbyPlayerRow::NativeConstruct()
{
	Super::NativeConstruct();

	if (KickButton)
	{
		KickButton->SetIsEnabled(false);
		if (GetWorld())
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (Controller)
			{
				bool Value = UKismetSystemLibrary::IsServer(GetWorld()) && Controller->PlayerState != PlayerStateRef;
				KickButton->SetIsEnabled(Value);
			}
		}
		KickButton->OnClicked.AddDynamic(this, &ULobbyPlayerRow::KickButtonClicked);
	}

	if (NameText && PlayerStateRef)
	{
		NameText->SetText(FText::FromString(PlayerStateRef->GetPlayerName()));
	}
}

void ULobbyPlayerRow::SpawnInitialize(APlayerState* Ref)
{
	PlayerStateRef = Ref;
}

void ULobbyPlayerRow::KickButtonClicked()
{

}