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
}

void AEvidenceGameMode::LoadSelectedGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Load game");

	UEvidenceGameInstance* const EvidenceGameInstance = GetGameInstance<UEvidenceGameInstance>();
	if (EvidenceGameInstance)
	{
		const FString& SlotName = EvidenceGameInstance->GetSlotName();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Loading ") + SlotName);

		FAsyncLoadGameFromSlotDelegate LoadedDelegate;
		LoadedDelegate.BindUObject(this, &ThisClass::OnLoadGameComplete);
		UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadedDelegate);
	}
}

void AEvidenceGameMode::OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
}

void AEvidenceGameMode::OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Successfully loaded ") + SlotName);
}
