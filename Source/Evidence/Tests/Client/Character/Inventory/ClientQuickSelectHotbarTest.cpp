// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientQuickSelectHotbarTest.h"

void AClientQuickSelectHotbarTest::StartTest()
{
	Super::StartTest();

	InjectInput(HotbarSlot8, FVector(1, 0, 0));
}

void AClientQuickSelectHotbarTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BaseCharacter->GetInventoryComponent()->GetSelectedIndex() == (CurrentSlotToTest - 1) && AltClientBaseCharacter->GetInventoryComponent()->GetSelectedIndex() == (CurrentSlotToTest - 1))
	{
		TestNextSlot();
	}
}

void AClientQuickSelectHotbarTest::TestNextSlot()
{
	CurrentSlotToTest -= 1;

	if (CurrentSlotToTest <= 0)
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		switch (CurrentSlotToTest)
		{
		case 1:
			InjectInput(HotbarSlot1, FVector(1, 0, 0));
			break;
		case 2:
			InjectInput(HotbarSlot2, FVector(1, 0, 0));
			break;
		case 3:
			InjectInput(HotbarSlot3, FVector(1, 0, 0));
			break;
		case 4:
			InjectInput(HotbarSlot4, FVector(1, 0, 0));
			break;
		case 5:
			InjectInput(HotbarSlot5, FVector(1, 0, 0));
			break;
		case 6:
			InjectInput(HotbarSlot6, FVector(1, 0, 0));
			break;
		case 7:
			InjectInput(HotbarSlot7, FVector(1, 0, 0));
			break;
		}
	}
}
