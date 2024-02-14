// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceGameMode.h"
#include "Character/EvidenceCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEvidenceGameMode::AEvidenceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
