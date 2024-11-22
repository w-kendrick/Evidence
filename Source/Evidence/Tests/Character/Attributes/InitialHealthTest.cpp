// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialHealthTest.h"

AInitialHealthTest::AInitialHealthTest()
{
	TimeLimit = 0.5f;
}

void AInitialHealthTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		bServerPassed = (ServerTestInfo.MyCharacter->GetHealth() == EXPECTED_HEALTH) && (ServerTestInfo.MyCharacter->GetMaxHealth() == EXPECTED_MAX_HEALTH);

		bServerPassed &= (ServerTestInfo.Client1Character->GetHealth() == EXPECTED_HEALTH) && (ServerTestInfo.Client1Character->GetMaxHealth() == EXPECTED_MAX_HEALTH);
		bClient1Passed = (Client1TestInfo.MyCharacter->GetHealth() == EXPECTED_HEALTH) && (Client1TestInfo.MyCharacter->GetMaxHealth() == EXPECTED_MAX_HEALTH);

		bServerPassed &= (ServerTestInfo.Client2Character->GetHealth() == EXPECTED_HEALTH) && (ServerTestInfo.Client2Character->GetMaxHealth() == EXPECTED_MAX_HEALTH);
		bClient2Passed = (Client2TestInfo.MyCharacter->GetHealth() == EXPECTED_HEALTH) && (Client2TestInfo.MyCharacter->GetMaxHealth() == EXPECTED_MAX_HEALTH);

		CheckResult();
	}
}
