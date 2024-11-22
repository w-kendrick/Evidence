// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialStaminaTest.h"

AInitialStaminaTest::AInitialStaminaTest()
{
	TimeLimit = 0.5f;
}

void AInitialStaminaTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		bServerPassed = (ServerTestInfo.MyCharacter->GetStamina() == EXPECTED_STAMINA) && (ServerTestInfo.MyCharacter->GetMaxStamina() == EXPECTED_MAX_STAMINA);

		bServerPassed &= (ServerTestInfo.Client1Character->GetStamina() == EXPECTED_STAMINA) && (ServerTestInfo.Client1Character->GetMaxStamina() == EXPECTED_MAX_STAMINA);
		bClient1Passed = (Client1TestInfo.MyCharacter->GetStamina() == EXPECTED_STAMINA) && (Client1TestInfo.MyCharacter->GetMaxStamina() == EXPECTED_MAX_STAMINA);

		bServerPassed &= (ServerTestInfo.Client2Character->GetStamina() == EXPECTED_STAMINA) && (ServerTestInfo.Client2Character->GetMaxStamina() == EXPECTED_MAX_STAMINA);
		bClient2Passed = (Client2TestInfo.MyCharacter->GetStamina() == EXPECTED_STAMINA) && (Client2TestInfo.MyCharacter->GetMaxStamina() == EXPECTED_MAX_STAMINA);

		CheckResult();
	}
}
