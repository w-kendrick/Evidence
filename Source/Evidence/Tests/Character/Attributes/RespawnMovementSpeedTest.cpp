// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnMovementSpeedTest.h"

ARespawnMovementSpeedTest::ARespawnMovementSpeedTest()
{
	TimeLimit = 7.5f;

	bPassedFirstCheck = false;
}

void ARespawnMovementSpeedTest::StartTest()
{
	Super::StartTest();

	UTestFunctionLibrary::StartSetupPeriod(GetWorld());

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.MyCharacter, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client1Character, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client2Character, KillPlayerEffectClass);

	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.MyCharacter, ZeroMovementSpeedEffectClass);
	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.Client1Character, ZeroMovementSpeedEffectClass);
	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.Client2Character, ZeroMovementSpeedEffectClass);
}

void ARespawnMovementSpeedTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if ((ServerTestInfo.MyCharacter->GetHealth() == DEATH_HEALTH) &&
			(ServerTestInfo.Client1Character->GetHealth() == DEATH_HEALTH) &&
			(Client1TestInfo.MyCharacter->GetHealth() == DEATH_HEALTH) &&
			(ServerTestInfo.Client2Character->GetHealth() == DEATH_HEALTH) &&
			(Client2TestInfo.MyCharacter->GetHealth() == DEATH_HEALTH))
		{
			bPassedFirstCheck = true;
		}

		if (bPassedFirstCheck)
		{
			if ((ServerTestInfo.MyCharacter->GetMoveSpeed() == RESPAWN_MOVEMENT_SPEED) &&
				(ServerTestInfo.Client1Character->GetMoveSpeed() == RESPAWN_MOVEMENT_SPEED) &&
				(Client1TestInfo.MyCharacter->GetMoveSpeed() == RESPAWN_MOVEMENT_SPEED) &&
				(ServerTestInfo.Client2Character->GetMoveSpeed() == RESPAWN_MOVEMENT_SPEED) &&
				(Client2TestInfo.MyCharacter->GetMoveSpeed() == RESPAWN_MOVEMENT_SPEED))
			{
				FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
			}
		}
	}
}