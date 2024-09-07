// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoreMovementGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace MoreMovementGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Prone, "InputTag.Prone", "Prone input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Sprint, "InputTag.Sprint", "Sprint input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MovementMode_Crouch, "MovementMode.Crouch", "Crouch movement mode.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MovementMode_Prone, "MovementMode.Prone", "Prone movement mode.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MovementMode_Sprint, "MovementMode.Sprint", "Sprint movement mode.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MovementMode_Walk, "MovementMode.Walk", "Walk movement mode.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MovementMode_Jump, "MovementMode.Jump", "Jump movement mode.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_Sprint, "GameplayCue.Sprint", "Sprint gameplay cue.");
}

