// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInventoryCycleDownTest.h"

AClientInventoryCycleDownTest::AClientInventoryCycleDownTest()
{
	TimeLimit = 5.0f;

	ExpectedIndex = 0;
	bFirstCycle = true;
}

void AClientInventoryCycleDownTest::StartTest()
{
	Super::StartTest();

	Cycle();
}

void AClientInventoryCycleDownTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if ((Client2TestInfo.MyCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex) &&
			(Client1TestInfo.OtherClientCharacter->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex) &&
			(ServerTestInfo.Client2Character->GetInventoryComponent()->GetSelectedIndex() == ExpectedIndex))
		{
			Cycle();
		}
	}
}

void AClientInventoryCycleDownTest::Cycle()
{
	if (bFirstCycle)
	{
		ExpectedIndex = UInventoryManagerComponent::INVENTORY_SIZE - 1;
		InjectInput(Client2TestInfo.InputSubsystem, CycleDownAction, FVector(1, 0, 0));
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

			InjectInput(Client2TestInfo.InputSubsystem, CycleDownAction, FVector(1, 0, 0));
		}
	}
}