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
				PlayerSave.PlayerID = PlayerState->UniqueId;

				if (ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerState->GetPlayerController()->GetPawn()))
				{
					PlayerSave.EquipmentList = Character->GetEquipmentList();
				}

				SaveGameInstance->AddPlayerSave(PlayerSave);
			}

			const FString& SlotNameString = EvidenceGameInstance->GetSlotName();
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, 0, SavedDelegate);
		}
	}
}

void AEvidenceGameMode::OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}
