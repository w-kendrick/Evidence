// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterSetupTest.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Tests/TestFunctionLibrary.h"

AEnterSetupTest::AEnterSetupTest()
{
	TimeLimit = 5.0f;
}

void AEnterSetupTest::StartTest()
{
	Super::StartTest();

	ServerTestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnServerMatchStateChanged);
	Client1TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient1MatchStateChanged);
	Client2TestInfo.MyGameState->OnMatchStateChanged.AddUObject(this, &ThisClass::OnClient2MatchStateChanged);

	AEvidenceGameMode* const EvidenceGameMode = UTestFunctionLibrary::GetEvidenceGameMode(GetWorld());
	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
	else
	{
		FinishTest(EFunctionalTestResult::Error, FString("The game mode is not AEvidenceGameMode"));
	}
}

void AEnterSetupTest::OnServerMatchStateChanged(FName State)
{
	bServerPassed = (State == MatchState::Setup);
	CheckResult();
}

void AEnterSetupTest::OnClient1MatchStateChanged(FName State)
{
	bClient1Passed = (State == MatchState::Setup);
	CheckResult();
}

void AEnterSetupTest::OnClient2MatchStateChanged(FName State)
{
	bClient2Passed = (State == MatchState::Setup);
	CheckResult();
}
