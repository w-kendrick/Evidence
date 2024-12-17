// Fill out your copyright notice in the Description page of Project Settings.


#include "PostNightTimeoutTest.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Items/Buttons/MatchStateButton.h"
#include "Evidence/Tests/TestFunctionLibrary.h"

APostNightTimeoutTest::APostNightTimeoutTest()
{
	TimeLimit = 15.0f;
}

void APostNightTimeoutTest::StartTest()
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

		Button->Interact(); //ends Night
	}
	else
	{
		FinishTest(EFunctionalTestResult::Error, FString("The level has no match state button"));
	}
}

void APostNightTimeoutTest::OnServerMatchStateChanged(FName State)
{
	bServerPassed = (State == MatchState::PreSetup);
	CheckResult();
}

void APostNightTimeoutTest::OnClient1MatchStateChanged(FName State)
{
	bClient1Passed = (State == MatchState::PreSetup);
	CheckResult();
}

void APostNightTimeoutTest::OnClient2MatchStateChanged(FName State)
{
	bClient2Passed = (State == MatchState::PreSetup);
	CheckResult();
}