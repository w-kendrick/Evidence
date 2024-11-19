// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInventorySizeTest.h"

AClientInventorySizeTest::AClientInventorySizeTest()
{
	TimeLimit = 5.0f;
}

void AClientInventorySizeTest::StartTest()
{
	Super::StartTest();

	bClient1Passed = (Client1TestInfo.OtherCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient2Passed = (Client2TestInfo.MyCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);

	CheckResult();
}
