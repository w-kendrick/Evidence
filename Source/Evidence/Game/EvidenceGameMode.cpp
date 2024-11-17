// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Evidence/Save/EvidenceSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Game/EvidenceGameInstance.h"
#include "Evidence/Game/EvidenceGameState.h"
#include "GameFramework/PlayerState.h"
#include "Evidence/Items/WorldGenerator.h"
#include "Evidence/Evidence.h"
#include "Evidence/Player/EvidencePlayerController.h"
#include "Evidence/Hub/Locker.h"
#include "Evidence/Character/Components/InventoryManagerComponent.h"
#include "Evidence/Hub/Hub.h"
#include "Evidence/Items/Equipment/EvidenceCaptureEquipment.h"

AEvidenceGameMode::AEvidenceGameMode()
	: Super()
{
	MaxSetupTime = 60.f; //60 for testing, 600 actual
	MaxNightTime = 180.f; //180 for testing, 1800 actual
	PostNightTime = 10.f;

	Night = DEFAULT_STARTING_NIGHT;
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
}

void AEvidenceGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
	Super::HandleStartingNewPlayer_Implementation(PlayerController);

	RestartPlayer(PlayerController);

	if (EvidenceSaveGame)
	{
		LoadPlayer(PlayerController);
	}
	else
	{
		PendingPlayerLoads.Add(PlayerController);
	}

	AddLivingPlayer(PlayerController);
}

void AEvidenceGameMode::Logout(AController* Controller)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		RemoveLivingPlayer(PlayerController, EPlayerLossType::Logout);
	}

	Super::Logout(Controller);
}

void AEvidenceGameMode::SetNight(const uint32 NewNight)
{
	Night = NewNight;
	EvidenceGameState->SetNight(Night);
}

#pragma region Match State

void AEvidenceGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	EvidenceGameState->SetMatchState(MatchState);

	if (MatchState == MatchState::InProgress)
	{
		SetMatchState(MatchState::PreSetup);
	}
	else if (MatchState == MatchState::PreSetup)
	{
		//Pre-setup begin
		UE_LOG(LogTemp, Warning, TEXT("Night: %d"), Night);

		for (APlayerController* const DeadPlayer : DeadPlayers)
		{
			AEvidencePlayerController* const EvidencePlayerController = Cast<AEvidencePlayerController>(DeadPlayer);
			if (EvidencePlayerController)
			{
				EvidencePlayerController->ClientSetIsSpectating(false);
			}

			ABaseCharacter* const BaseCharacter = Cast<ABaseCharacter>(DeadPlayer->GetPawn());
			if (BaseCharacter)
			{
				BaseCharacter->ResetAttributes();
			}

			LivingPlayers.Add(DeadPlayer);
		}

		DeadPlayers.Empty();
	}
	else if (MatchState == MatchState::Setup)
	{
		GetWorldTimerManager().SetTimer(SetupHandle, this, &ThisClass::StartNight, MaxSetupTime, false);
		SetupWorld();
	}
	else if (MatchState == MatchState::Night)
	{
		GetWorldTimerManager().SetTimer(NightHandle, this, &ThisClass::EndNight, MaxNightTime, false);
	}
	else if (MatchState == MatchState::PostNight)
	{
		GetWorldTimerManager().SetTimer(PostNightHandle, this, &ThisClass::StartPreSetup, PostNightTime, false);
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

void AEvidenceGameMode::StartPreSetup()
{
	EvidenceGameState->EndNight();
	SetNight(Night + 1);
	ResetWorld(false);
	SaveGame();

	SetMatchState(MatchState::PreSetup);
}

void AEvidenceGameMode::EndPreSetup()
{
	SetMatchState(MatchState::Setup);
}

void AEvidenceGameMode::TeamWipe()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Wipe reset");

	SetNight(DEFAULT_STARTING_NIGHT);
	EvidenceGameState->SetCash(DEFAULT_STARTING_CASH);
	ResetWorld(true);
	WipeSave();

	SetMatchState(MatchState::PreSetup);
}

#pragma endregion

#pragma region World Generation

void AEvidenceGameMode::SetupWorld()
{
	FetchWorldGenerators();

	for (AWorldGenerator* const WorldGenerator : WorldGenerators)
	{
		WorldGenerator->SetupWorld();
	}
}

void AEvidenceGameMode::ResetWorld(const bool bWasWipe)
{
	FetchWorldGenerators();

	for (AWorldGenerator* const WorldGenerator : WorldGenerators)
	{
		WorldGenerator->ResetWorld();
	}

	ResetEquipment(bWasWipe);
}

void AEvidenceGameMode::ResetEquipment(const bool bWasWipe)
{
	AHub* const Hub = EvidenceGameState->GetHub();
	const TArray<AEvidenceCaptureEquipment*>& HubCaptureDevices = Hub->GetCaptureDevices();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEquipment::StaticClass(), Actors);

	for (AActor* const Actor : Actors)
	{
		AEquipment* const Equipment = Cast<AEquipment>(Actor);

		if (bWasWipe)
		{
			Equipment->Destroy();
		}
		else
		{
			if (Equipment->GetOwner() == nullptr && !HubCaptureDevices.Contains(Equipment))
			{
				Equipment->Destroy();
			}

			ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

			if (Locker)
			{
				Locker->WipeNotify();
			}
		}
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
			SaveGameInstance->SetNight(Night);

			for (const APlayerState* const PlayerState : EvidenceGameState->PlayerArray)
			{
				FPlayerSave PlayerSave;

				if (ABaseCharacter* const Character = Cast<ABaseCharacter>(PlayerState->GetPlayerController()->GetPawn()))
				{
					const FEquipmentList& EquipmentList = Character->GetEquipmentList();
					for (uint8 i = 0; i < UInventoryManagerComponent::INVENTORY_SIZE; i++)
					{
						const FEquipmentItem& EquipmentItem = EquipmentList[i];
						AEquipment* const Equipment = EquipmentItem.GetEquipment();

						FEquipmentSaveData EquipmentData;
						SaveEquipment(EquipmentData, Equipment);

						PlayerSave.AddEquipment(EquipmentData);
					}
				}
				UE_LOG(LogTemp, Warning, TEXT("Adding PlayerSave for %s with %d instances of equipment"), *PlayerState->GetUniqueId().ToString(), PlayerSave.SavedEquipment.Num());
				SaveGameInstance->AddPlayerSave(PlayerState->GetUniqueId(), PlayerSave);
			}

			SaveLocker(SaveGameInstance);

			const FString& SlotNameString = EvidenceGameInstance->GetSlotName();
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, 0, SavedDelegate);
		}
	}
}

void AEvidenceGameMode::SaveLocker(UEvidenceSaveGame* const SaveGame) const
{
	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	if (Locker)
	{
		const FEquipmentList& LockerStorage = Locker->GetStorage();

		for (uint8 Index = 0; Index < ALocker::STORAGE_CAPACITY; Index++)
		{
			AEquipment* const Equipment = LockerStorage[Index].GetEquipment();

			FEquipmentSaveData EquipmentData;
			SaveEquipment(EquipmentData, Equipment);

			SaveGame->AddLockerEquipment(EquipmentData);
		}
	}
}

void AEvidenceGameMode::SaveEquipment(FEquipmentSaveData& EquipmentData, AEquipment* const Equipment) const
{
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

void AEvidenceGameMode::LoadPlayer(const APlayerController* const PlayerController) const
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

			AEquipment* const NewEquipment = LoadEquipment(EquipmentData);

			Character->Pickup(NewEquipment, i);
		}
	}
}

void AEvidenceGameMode::LoadLocker() const
{
	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	if (Locker)
	{
		const TArray<FEquipmentSaveData>& LockerEquipment = EvidenceSaveGame->GetLockerEquipment();

		uint8 Index = 0;
		while (Index < ALocker::STORAGE_CAPACITY && Index < LockerEquipment.Num())
		{
			const FEquipmentSaveData& EquipmentSaveData = LockerEquipment[Index];

			AEquipment* const NewEquipment = LoadEquipment(EquipmentSaveData);
			Locker->SetEquipmentAtIndex(NewEquipment, Index);

			Index++;
		}
	}
}

AEquipment* AEvidenceGameMode::LoadEquipment(const FEquipmentSaveData EquipmentSaveData) const
{
	AEquipment* NewEquipment = nullptr;

	const TSubclassOf<AEquipment>& EquipmentClass = GetEquipmentClass(EquipmentSaveData.EquipmentID);

	if (EquipmentClass)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		NewEquipment = GetWorld()->SpawnActor<AEquipment>(EquipmentClass, DefaultTransform);

		FMemoryReader MemReader(EquipmentSaveData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
		Ar.ArIsSaveGame = true;
		// Convert binary array back into actor's variables
		NewEquipment->Serialize(Ar);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Spawned and reloaded ") + NewEquipment->GetEquipmentName());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("No need to spawn null equipment"));
	}

	return NewEquipment;
}

void AEvidenceGameMode::WipeSave()
{
	if (const UEvidenceGameInstance* const EvidenceGameInstance = Cast<UEvidenceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (UEvidenceSaveGame* const SaveGameInstance = Cast<UEvidenceSaveGame>(UGameplayStatics::CreateSaveGameObject(UEvidenceSaveGame::StaticClass())))
		{
			FAsyncSaveGameToSlotDelegate SavedDelegate;
			SavedDelegate.BindUObject(this, &ThisClass::OnSaveGameComplete);

			const FString& SlotNameString = EvidenceGameInstance->GetSlotName();
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, 0, SavedDelegate);
			UE_LOG(LogTemp, Warning, TEXT("Wiped Save"));
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
		SetNight(EvidenceSaveGame->GetNight());
		EvidenceGameState->SetCash(EvidenceSaveGame->GetCash());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Loaded UEvidenceSaveGame - Night ") + FString::FromInt(Night));
		for (const APlayerController* const PlayerController : PendingPlayerLoads)
		{
			LoadPlayer(PlayerController);
		}

		LoadLocker();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString("Loaded default save game"));
		EvidenceSaveGame = Cast<UEvidenceSaveGame>(UGameplayStatics::CreateSaveGameObject(UEvidenceSaveGame::StaticClass()));
	}
}

#pragma endregion

#pragma region Living Players

void AEvidenceGameMode::OnPlayerDeath(APlayerController* Player)
{
	RemoveLivingPlayer(Player, EPlayerLossType::Death);

	AEvidencePlayerController* const EvidencePlayerController = Cast<AEvidencePlayerController>(Player);
	if (EvidencePlayerController)
	{
		EvidencePlayerController->ClientSetIsSpectating(true);
	}
}

void AEvidenceGameMode::AddLivingPlayer(APlayerController* Player)
{
	LivingPlayers.Add(Player);
	EvidenceGameState->AddLivingPlayer(Player);
}

void AEvidenceGameMode::RemoveLivingPlayer(APlayerController* Player, const EPlayerLossType LossType)
{
	LivingPlayers.Remove(Player);
	EvidenceGameState->RemoveLivingPlayer(Player);

	if (LossType == EPlayerLossType::Death)
	{
		DeadPlayers.Add(Player);

		if (LivingPlayers.Num() == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "All players dead");
			FTimerHandle WipeTimer;
			GetWorldTimerManager().SetTimer(WipeTimer, this, &ThisClass::TeamWipe, 5.0f, false);
		}
	}
	else if (LossType == EPlayerLossType::Logout && DeadPlayers.Contains(Player))
	{
		DeadPlayers.Remove(Player);
	}
}

#pragma endregion