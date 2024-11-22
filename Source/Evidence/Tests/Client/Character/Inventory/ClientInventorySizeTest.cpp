// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInventorySizeTest.h"

AClientInventorySizeTest::AClientInventorySizeTest()
{
	TimeLimit = 5.0f;
}

void AClientInventorySizeTest::StartTest()
{
	Super::StartTest();

	bServerPassed = (ServerTestInfo.MyCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient1Passed = (Client1TestInfo.ServerCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient2Passed = (Client2TestInfo.ServerCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);

	bServerPassed &= (ServerTestInfo.Client1Character->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient1Passed &= (Client1TestInfo.MyCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient2Passed &= (Client2TestInfo.OtherClientCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);

	bServerPassed &= (ServerTestInfo.Client2Character->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient1Passed &= (Client1TestInfo.OtherClientCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);
	bClient2Passed &= (Client2TestInfo.MyCharacter->GetInventoryComponent()->GetInventory().GetNum() == UInventoryManagerComponent::INVENTORY_SIZE);

	CheckResult();
}
