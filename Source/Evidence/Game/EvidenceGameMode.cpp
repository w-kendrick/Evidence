// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Evidence/Save/EvidenceSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Game/EvidenceGameInstance.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "GameFramework/PlayerState.h"
#include "Evidence/Items/WorldGenerator.h"

AEvidenceGameMode::AEvidenceGameMode()
	: Super()
{
	MaxSetupTime = 600.f;
	MaxNightTime = 1800.f;
}

void AEvidenceGameMode::InitGameState()
{
	EvidenceGameState = Cast<AEvidenceGameState>(GameState);

	if (EvidenceGameState)
	{
		EvidenceGameState->SetSetupCountdownLength(MaxSetupTime);
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

	if (EvidenceSaveGame)
	{
		LoadPlayer(PlayerController);
	}
	else
	{
		PendingPlayerLoads.Add(PlayerController);
	}
}

#pragma region Match State

void AEvidenceGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	EvidenceGameState->SetMatchState(MatchState);

	if (MatchState == MatchState::InProgress)
	{
		SetMatchState(MatchState::Setup);
	}
	else if (MatchState == MatchState::Setup)
	{
		GetWorldTimerManager().SetTimer(SetupHandle, this, &ThisClass::StartNight, MaxSetupTime, false);
	}
	else if (MatchState == MatchState::Night)
	{
		GetWorldTimerManager().SetTimer(NightHandle, this, &ThisClass::EndNight, MaxNightTime, false);
	}
}

void AEvidenceGameMode::StartNight()
{
	GetWorldTimerManager().ClearTimer(SetupHandle);

	SetMatchState(MatchState::Night);
}

void AEvidenceGameMode::EndNight()
{
	GetWorldTimerManager().ClearTimer(NightHandle);

	SetMatchState(MatchState::PostNight);
}

#pragma endregion

#pragma region World Generation

void AEvidenceGameMode::TriggerWorldGeneration()
{
	FetchWorldGenerators();

	for (AWorldGenerator* const WorldGenerator : WorldGenerators)
	{
		WorldGenerator->SetupWorld();
	}
}

void AEvidenceGameMode::ResetWorld()
{
	FetchWorldGenerators();

	for (AWorldGenerator* const WorldGenerator : WorldGenerators)
	{
		WorldGenerator->ResetWorld();
	}
}

void AEvidenceGameMode::FetchWorldGenerators()
{
	WorldGenerators.Empty();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldGenerator::StaticClass(), FoundActors);

	for (AActor* const Actor : FoundActors)
	{
		AWorldGenerator* const WorldGenerator = Cast<AWorldGenerator>(Actor);
		WorldGenerators.Add(WorldGenerator);
	}
}

#pragma endregion

#pragma region Save and Load

uint8 AEvidenceGameMode::GetEquipmentID(const AEquipment* const Equipment) const
{
	uint8 Result = 0;

	if (Equipment)
	{
		for (const FEquipmentToID& Elem : EquipmentClassMap)
		{
			if (Equipment->GetClass() == Elem.Class)
			{
				Result = Elem.ID;
			}
		}
	}

	return Result;
}

TSubclassOf<AEquipment> AEvidenceGameMode::GetEquipmentClass(const uint8 ID) const
{
	TSubclassOf<AEquipment> Result = nullptr;

	for (const FEquipmentToID& Elem : EquipmentClassMap)
	{
		if (ID == Elem.ID)
		{
			Result = Elem.Class;
		}
	}

	return Result;
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
					const FEquipmentList& EquipmentList = Character->GetEquipmentList();
					for (uint8 i = 0; i < INVENTORY_SIZE; i++)
					{
						const FEquipmentItem& EquipmentItem = EquipmentList[i];
						AEquipment* const Equipment = EquipmentItem.GetEquipment();

						FEquipmentSaveData EquipmentData;
						EquipmentData.EquipmentID = GetEquipmentID(Equipment);

						if (Equipment)
						{
							// Pass the array to fill with data from Actor
							FMemoryWriter MemWriter(EquipmentData.ByteData);

							FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
							// Find only variables with UPROPERTY(SaveGame)
							Ar.ArIsSaveGame = true;
							// Converts Actor's SaveGame UPROPERTIES into binary array
							Equipment->Serialize(Ar);
						}

						PlayerSave.AddEquipment(EquipmentData);
					}
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("Adding PlayerSave for ") + PlayerState->UniqueId.ToString() + FString(" with ") + FString::FromInt(PlayerSave.SavedEquipment.Num()) + FString(" instances of equipment"));
				SaveGameInstance->AddPlayerSave(PlayerState->GetUniqueId(), PlayerSave);
			}

			const FString& SlotNameString = EvidenceGameInstance->GetSlotName();
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, 0, SavedDelegate);
		}
	}
}

void AEvidenceGameMode::LoadSelectedGame()
{
	UEvidenceGameInstance* const EvidenceGameInstance = GetGameInstance<UEvidenceGameInstance>();
	if (EvidenceGameInstance)
	{
		const FString& SlotName = EvidenceGameInstance->GetSlotName();

		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			FAsyncLoadGameFromSlotDelegate LoadedDelegate;
			LoadedDelegate.BindUObject(this, &ThisClass::OnLoadGameComplete);
			UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadedDelegate);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString("SAVE GAME DOES NOT EXIST"));
		}
	}
}

void AEvidenceGameMode::LoadPlayer(const APlayerController* const PlayerController)
{
	const FUniqueNetIdRepl& ID = PlayerController->PlayerState->GetUniqueId();
	ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerController->GetPawn());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString("Load player ") + ID.ToString());

	FPlayerSave PlayerSave;
	if (EvidenceSaveGame->GetPlayerSave(ID, PlayerSave) && Character)
	{
		for (uint8 i = 0; i < PlayerSave.SavedEquipment.Num(); i++)
		{
			const FEquipmentSaveData& EquipmentData = PlayerSave.SavedEquipment[i];
			const TSubclassOf<AEquipment>& EquipmentClass = GetEquipmentClass(EquipmentData.EquipmentID);

			if (EquipmentClass)
			{
				FActorSpawnParameters Params;
				Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AEquipment* const NewEquipment = GetWorld()->SpawnActor<AEquipment>(EquipmentClass, DefaultTransform);

				FMemoryReader MemReader(EquipmentData.ByteData);

				FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
				Ar.ArIsSaveGame = true;
				// Convert binary array back into actor's variables
				NewEquipment->Serialize(Ar);

				Character->Pickup(NewEquipment, i);

				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Spawned and reloaded ") + NewEquipment->GetEquipmentName());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("No need to spawn null equipment"));
			}
		}
	}
}

void AEvidenceGameMode::OnSaveGameComplete(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (bSuccess ? FString("Successfully") : FString("Unsuccessfully")) + FString(" saved ") + SlotName);
}

void AEvidenceGameMode::OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	EvidenceSaveGame = Cast<UEvidenceSaveGame>(LoadedGameData);

	if (EvidenceSaveGame)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Loaded UEvidenceSaveGame"));
		for (const APlayerController* const PlayerController : PendingPlayerLoads)
		{
			LoadPlayer(PlayerController);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Loaded default save game"));
		EvidenceSaveGame = Cast<UEvidenceSaveGame>(UGameplayStatics::CreateSaveGameObject(UEvidenceSaveGame::StaticClass()));
	}
}

#pragma endregion