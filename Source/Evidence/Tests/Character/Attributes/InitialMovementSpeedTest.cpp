// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialMovementSpeedTest.h"

AInitialMovementSpeedTest::AInitialMovementSpeedTest()
{
	TimeLimit = 0.5f;
}

void AInitialMovementSpeedTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		bServerPassed = (ServerTestInfo.MyCharacter->GetMoveSpeed() == EXPECTED_MOVEMENT_SPEED) && (ServerTestInfo.MyCharacter->GetMaxMoveSpeed() == EXPECTED_MAX_MOVEMENT_SPEED);

		bServerPassed &= (ServerTestInfo.Client1Character->GetMoveSpeed() == EXPECTED_MOVEMENT_SPEED) && (ServerTestInfo.Client1Character->GetMaxMoveSpeed() == EXPECTED_MAX_MOVEMENT_SPEED);
		bClient1Passed = (Client1TestInfo.MyCharacter->GetMoveSpeed() == EXPECTED_MOVEMENT_SPEED) && (Client1TestInfo.MyCharacter->GetMaxMoveSpeed() == EXPECTED_MAX_MOVEMENT_SPEED);

		bServerPassed &= (ServerTestInfo.Client2Character->GetMoveSpeed() == EXPECTED_MOVEMENT_SPEED) && (ServerTestInfo.Client2Character->GetMaxMoveSpeed() == EXPECTED_MAX_MOVEMENT_SPEED);
		bClient2Passed = (Client2TestInfo.MyCharacter->GetMoveSpeed() == EXPECTED_MOVEMENT_SPEED) && (Client2TestInfo.MyCharacter->GetMaxMoveSpeed() == EXPECTED_MAX_MOVEMENT_SPEED);

		CheckResult();
	}
}