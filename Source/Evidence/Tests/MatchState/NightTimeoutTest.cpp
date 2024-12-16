// Fill out your copyright notice in the Description page of Project Settings.


#include "NightTimeoutTest.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Items/Buttons/MatchStateButton.h"
#include "Evidence/Tests/TestFunctionLibrary.h"

ANightTimeoutTest::ANightTimeoutTest()
{
	TimeLimit = 185.0f;
}

void ANightTimeoutTest::StartTest()
{
	Super::StartTest();

	ServerTestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnServerMatchStateChanged);
	Client1TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient1MatchStateChanged);
	Client2TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient2MatchStateChanged);

	AMatchStateButton* const Button = UTestFunctionLibrary::GetMatchStateButton(GetWorld());
	if (Button)
	{
		Button->Interact(); //ends Pre-Setup

		Button->Interact(); //ends Setup
	}
	else
	{
		FinishTest(EFunctionalTestResult::Error, FString("The level has no match state button"));
	}
}

void ANightTimeoutTest::OnServerMatchStateChanged(FName State)
{
	bServerPassed = (State == MatchState::PostNight);
	CheckResult();
}

void ANightTimeoutTest::OnClient1MatchStateChanged(FName State)
{
	bClient1Passed = (State == MatchState::PostNight);
	CheckResult();
}

void ANightTimeoutTest::OnClient2MatchStateChanged(FName State)
{
	bClient2Passed = (State == MatchState::PostNight);
	CheckResult();
}
