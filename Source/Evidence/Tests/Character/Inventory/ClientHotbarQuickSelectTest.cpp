// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientHotbarQuickSelectTest.h"

AClientHotbarQuickSelectTest::AClientHotbarQuickSelectTest()
{
	TimeLimit = 5.0f;

	ExpectedIndex = 0;
	bFirstCycle = true;
}

void AClientHotbarQuickSelectTest::StartTest()
{
	Super::StartTest();

	Cycle();
}

void AClientHotbarQuickSelectTest::Tick(float DeltaTime)
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

void AClientHotbarQuickSelectTest::Cycle()
{
	if (bFirstCycle)
	{
		ExpectedIndex = UInventoryManagerComponent::INVENTORY_SIZE - 1;
		InjectInput(Client2TestInfo.InputSubsystem, ChooseInputAction(), FVector(1, 0, 0));
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

			InjectInput(Client2TestInfo.InputSubsystem, ChooseInputAction(), FVector(1, 0, 0));
		}
	}
}

UInputAction* AClientHotbarQuickSelectTest::ChooseInputAction() const
{
	UInputAction* Action = nullptr;

	switch (ExpectedIndex)
	{
	case 0:
		Action = Hotbar1Action;
		break;
	case 1:
		Action = Hotbar2Action;
		break;
	case 2:
		Action = Hotbar3Action;
		break;
	case 3:
		Action = Hotbar4Action;
		break;
	case 4:
		Action = Hotbar5Action;
		break;
	case 5:
		Action = Hotbar6Action;
		break;
	case 6:
		Action = Hotbar7Action;
		break;
	case 7:
		Action = Hotbar8Action;
		break;
	default:
		break;
	}

	return Action;
}
