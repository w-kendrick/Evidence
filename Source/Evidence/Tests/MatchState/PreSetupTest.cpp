// Fill out your copyright notice in the Description page of Project Settings.


#include "PreSetupTest.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Tests/TestFunctionLibrary.h"

APreSetupTest::APreSetupTest()
{
}

void APreSetupTest::StartTest()
{
	Super::StartTest();

	AEvidenceGameMode* const EvidenceGameMode = UTestFunctionLibrary::GetEvidenceGameMode(GetWorld());
	if (EvidenceGameMode)
	{
		if (EvidenceGameMode->GetMatchState() == MatchState::PreSetup)
		{
			FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
		}
		else
		{
			FinishTest(EFunctionalTestResult::Failed, FString("The game mode initial match state isn't Pre-Setup"));
		}
	}
	else
	{
		FinishTest(EFunctionalTestResult::Error, FString("The game mode is not AEvidenceGameMode"));
	}
}
