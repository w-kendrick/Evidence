// Fill out your copyright notice in the Description page of Project Settings.


#include "SetupTimeoutTest.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Items/Buttons/MatchStateButton.h"
#include "Evidence/Tests/TestFunctionLibrary.h"

ASetupTimeoutTest::ASetupTimeoutTest()
{
	TimeLimit = 65.0f;
}

void ASetupTimeoutTest::StartTest()
{
	Super::StartTest();

	ServerTestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnServerMatchStateChanged);
	Client1TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient1MatchStateChanged);
	Client2TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient2MatchStateChanged);

	AMatchStateButton* const Button = UTestFunctionLibrary::GetMatchStateButton(GetWorld());
	if (Button)
	{
		Button->Interact(); //ends Pre-Setup
	}
	else
	{
		FinishTest(EFunctionalTestResult::Error, FString("The game mode is not AEvidenceGameMode"));
	}
}

void ASetupTimeoutTest::OnServerMatchStateChanged(FName State)
{
	bServerPassed = (State == MatchState::Night);
	CheckResult();
}

void ASetupTimeoutTest::OnClient1MatchStateChanged(FName State)
{
	bClient1Passed = (State == MatchState::Night);
	CheckResult();
}

void ASetupTimeoutTest::OnClient2MatchStateChanged(FName State)
{
	bClient2Passed = (State == MatchState::Night);
	CheckResult();
}
