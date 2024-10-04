// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Evidence/Save/EvidenceSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/EvidenceGameInstance.h"
#include "Evidence/EvidenceGameState.h"
#include "GameFramework/PlayerState.h"

AEvidenceGameMode::AEvidenceGameMode()
	: Super()
{

}

void AEvidenceGameMode::InitGameState()
{
	EvidenceGameState = Cast<AEvidenceGameState>(GameState);
}

void AEvidenceGameMode::SaveGame()
{
	if (const UEvidenceGameInstance* const EvidenceGameInstance = Cast<UEvidenceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (UEvidenceSaveGame* const SaveGameInstance = Cast<UEvidenceSaveGame>(UGameplayStatics::CreateSaveGameObject(UEvidenceSaveGame::StaticClass())))
		{
			FAsyncSaveGameToSlotDelegate SavedDelegate;
			SavedDelegate.BindUObject(this, &ThisClass::OnSaveGameComplete);

			SaveGameInstance->SetCash(EvidenceGameState->GetCash());
			SaveGameInstance->SetNight(0U);

			for (const APlayerState* const PlayerState : EvidenceGameState->PlayerArray)
			{
				FPlayerSave PlayerSave;

				if (ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerState->GetPlayerController()->GetPawn()))
				{
					PlayerSave.EquipmentList = Character->GetEquipmentList();
				}

				SaveGameInstance->AddPlayerSave(PlayerState->UniqueId, PlayerSave);
			}

			const FString& SlotNameString = EvidenceGameInstance->GetSlotName();
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, 0, SavedDelegate);
		}
	}
}

void AEvidenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadSelectedGame();

	GetWorldTimerManager().SetTimer(SaveHandle, this, &ThisClass::SaveGame, 20.f, true);
}

void AEvidenceGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
	Super::HandleStartingNewPlayer_Implementation(PlayerController);

	const FUniqueNetIdRepl NewPlayerID = PlayerController->PlayerState->GetUniqueId();

	if (EvidenceSaveGame)
	{
		LoadPlayer(NewPlayerID);
	}
	else
	{
		PendingPlayerLoads.Add(NewPlayerID);
	}
}

void AEvidenceGameMode::LoadSelectedGame()
{
	UEvidenceGameInstance* const EvidenceGameInstance = GetGameInstance<UEvidenceGameInstance>();
	if (EvidenceGameInstance)
	{
		const FString& SlotName = EvidenceGameInstance->GetSlotName();

		FAsyncLoadGameFromSlotDelegate LoadedDelegate;
		LoadedDelegate.BindUObject(this, &ThisClass::OnLoadGameComplete);
		UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadedDelegate);
	}
}

void AEvidenceGameMode::LoadPlayer(const FUniqueNetIdRepl& ID)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString("Load player ") + ID.ToString());

	FPlayerSave PlayerSave;
	if (EvidenceSaveGame->GetPlayerSave(ID, PlayerSave))
	{
		const FEquipmentList& EquipmentList = PlayerSave.EquipmentList;

		for (uint8 i = 0; i < INVENTORY_SIZE; i++)
		{
			AEquipment* const Equipment = EquipmentList[i].GetEquipment();
			if (Equipment)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Equipment->GetEquipmentName());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("Equipment is null"));
			}
		}
	}
}

void AEvidenceGameMode::OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("Successfully saved ") + SlotName);
}

void AEvidenceGameMode::OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	EvidenceSaveGame = Cast<UEvidenceSaveGame>(LoadedGameData);

	for (const FUniqueNetIdRepl& ID : PendingPlayerLoads)
	{
		LoadPlayer(ID);
	}
}
