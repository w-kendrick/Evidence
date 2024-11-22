// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerInventoryCycleDownTest.h"

AServerInventoryCycleDownTest::AServerInventoryCycleDownTest()
{
	TimeLimit = 5.0f;

	ExpectedIndex = 0;
	bFirstCycle = true;
}

void AServerInventoryCycleDownTest::StartTest()
{
	Super::StartTest();

	Cycle();
}

void AServerInventoryCycleDownTest::Tick(float DeltaTime)
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

void AServerInventoryCycleDownTest::Cycle()
{
	if (bFirstCycle)
	{
		ExpectedIndex = UInventoryManagerComponent::INVENTORY_SIZE - 1;
		InjectInput(ServerTestInfo.InputSubsystem, CycleDownAction, FVector(1, 0, 0));
		bFirstCycle = false;
	}
	else
	{
		if (ExpectedIndex == UInventoryManagerComponent::INVENTORY_SIZE - 1)
		{
			FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
		}
		else
		{
			ExpectedIndex--;
			if (ExpectedIndex < 0)
			{
				ExpectedIndex += UInventoryManagerComponent::INVENTORY_SIZE;
			}

			InjectInput(ServerTestInfo.InputSubsystem, CycleDownAction, FVector(1, 0, 0));
		}
	}
}