// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnStaminaTest.h"

ARespawnStaminaTest::ARespawnStaminaTest()
{
	TimeLimit = 7.5f;

	bPassedFirstCheck = false;
}

void ARespawnStaminaTest::StartTest()
{
	Super::StartTest();

	UTestFunctionLibrary::StartSetupPeriod(GetWorld());

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.MyCharacter, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client1Character, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client2Character, KillPlayerEffectClass);

	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.MyCharacter, ZeroStaminaEffectClass);
	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.Client1Character, ZeroStaminaEffectClass);
	UTestFunctionLibrary::ApplyGameplayEffect(ServerTestInfo.Client2Character, ZeroStaminaEffectClass);
}

void ARespawnStaminaTest::Tick(float DeltaTime)
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
			if ((ServerTestInfo.MyCharacter->GetStamina() == RESPAWN_STAMINA) &&
				(ServerTestInfo.Client1Character->GetStamina() == RESPAWN_STAMINA) &&
				(Client1TestInfo.MyCharacter->GetStamina() == RESPAWN_STAMINA) &&
				(ServerTestInfo.Client2Character->GetStamina() == RESPAWN_STAMINA) &&
				(Client2TestInfo.MyCharacter->GetStamina() == RESPAWN_STAMINA))
			{
				FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
			}
		}
	}
}