// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerInventoryCycleUpTest.h"

AServerInventoryCycleUpTest::AServerInventoryCycleUpTest()
{
	TimeLimit = 5.0f;

	ExpectedIndex = 0;
	bFirstCycle = true;
}

void AServerInventoryCycleUpTest::StartTest()
{
	Super::StartTest();

	Cycle();
}

void AServerInventoryCycleUpTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if ((Client2TestInfo.ServerCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex) &&
			(Client1TestInfo.ServerCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex) &&
			(ServerTestInfo.MyCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex))
		{
			Cycle();
		}
	}
}

void AServerInventoryCycleUpTest::Cycle()
{
	if (bFirstCycle)
	{
		ExpectedIndex++;
		InjectInput(ServerTestInfo.InputSubsystem, CycleUpAction, FVector(1, 0, 0));
		bFirstCycle = false;
	}
	else
	{
		if (ExpectedIndex == 0)
		{
			FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
		}
		else
		{
			ExpectedIndex = (ExpectedIndex + 1) % UInventoryManagerComponent::INVENTORY_SIZE;
			InjectInput(ServerTestInfo.InputSubsystem, CycleUpAction, FVector(1, 0, 0));
		}
	}
}