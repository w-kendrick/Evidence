// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Evidence : ModuleRules
{
	public Evidence(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NetCore", "EnhancedInput", "AIModule", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "AbilityInputSystem", "ProneMovementMode" });
	}
}
