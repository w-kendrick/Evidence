// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnHealthTest.h"

ARespawnHealthTest::ARespawnHealthTest()
{
	TimeLimit = 7.5f;

	Expected_Health = 0.0f;
	bPassedFirstCheck = false;
}

void ARespawnHealthTest::StartTest()
{
	Super::StartTest();

	UTestFunctionLibrary::StartSetupPeriod(GetWorld());

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.MyCharacter, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client1Character, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client2Character, KillPlayerEffectClass);
}

void ARespawnHealthTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if ((ServerTestInfo.MyCharacter->GetHealth() == Expected_Health) &&
			(ServerTestInfo.Client1Character->GetHealth() == Expected_Health) &&
			(Client1TestInfo.MyCharacter->GetHealth() == Expected_Health) &&
			(ServerTestInfo.Client2Character->GetHealth() == Expected_Health) &&
			(Client2TestInfo.MyCharacter->GetHealth() == Expected_Health))
		{
			if (bPassedFirstCheck)
			{
				FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
			}
			else
			{
				Expected_Health = 100.f;
				bPassedFirstCheck = true;
			}
		}
	}
}
