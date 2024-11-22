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
		bServerPassed = (ServerTestInfo.MyCharacter->GetStamina() == 100.f) && (ServerTestInfo.MyCharacter->GetMaxStamina() == 100.f);

		bServerPassed &= (ServerTestInfo.Client1Character->GetStamina() == 100.f) && (ServerTestInfo.Client1Character->GetMaxStamina() == 100.f);
		bClient1Passed = (Client1TestInfo.MyCharacter->GetStamina() == 100.f) && (Client1TestInfo.MyCharacter->GetMaxStamina() == 100.f);

		bServerPassed &= (ServerTestInfo.Client2Character->GetStamina() == 100.f) && (ServerTestInfo.Client2Character->GetMaxStamina() == 100.f);
		bClient2Passed = (Client2TestInfo.MyCharacter->GetStamina() == 100.f) && (Client2TestInfo.MyCharacter->GetMaxStamina() == 100.f);

		CheckResult();
	}
}
