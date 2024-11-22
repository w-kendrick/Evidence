// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInventoryCycleUpTest.h"

AClientInventoryCycleUpTest::AClientInventoryCycleUpTest()
{
	TimeLimit = 5.0f;

	ExpectedIndex = 0;
	bFirstCycle = true;
}

void AClientInventoryCycleUpTest::StartTest()
{
	Super::StartTest();

	Cycle();
}

void AClientInventoryCycleUpTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if ((Client2TestInfo.MyCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex) &&
			(Client1TestInfo.OtherClientCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex))
		{
			Cycle();
		}
	}
}

void AClientInventoryCycleUpTest::Cycle()
{
	if (bFirstCycle)
	{
		ExpectedIndex++;
		InjectInput(Client2TestInfo.InputSubsystem, CycleUpAction, FVector(1, 0, 0));
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
			InjectInput(Client2TestInfo.InputSubsystem, CycleUpAction, FVector(1, 0, 0));
		}
	}
}
