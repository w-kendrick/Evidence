// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInitialStaminaTest.h"

AClientInitialStaminaTest::AClientInitialStaminaTest()
{
}

void AClientInitialStaminaTest::StartTest()
{
	Super::StartTest();

	const bool Client1_Result = (Client1TestInfo.MyCharacter->GetStamina() == 100.f) && (Client1TestInfo.MyCharacter->GetMaxStamina() == 100.f);
	const bool Client2_Result = (Client2TestInfo.MyCharacter->GetStamina() == 100.f) && (Client2TestInfo.MyCharacter->GetMaxStamina() == 100.f);

	if (Client1_Result && Client2_Result)
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}