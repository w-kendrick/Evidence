// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerStorageVisibilityTest.h"
#include "Evidence/Hub/Locker.h"

ALockerStorageVisibilityTest::ALockerStorageVisibilityTest()
{
}

void ALockerStorageVisibilityTest::StartTest()
{
	Super::StartTest();

	ServerTestEquipment = Cast<AEquipment>(UGameplayStatics::GetActorOfClass(GetWorld(), AEquipment::StaticClass()));
	Client1TestEquipment = Cast<AEquipment>(UMPTestHelpersBPLibrary::GetClientActorOfClass(AEquipment::StaticClass(), 0));
	Client2TestEquipment = Cast<AEquipment>(UMPTestHelpersBPLibrary::GetClientActorOfClass(AEquipment::StaticClass(), 1));

	if (!ServerTestEquipment || !Client1TestEquipment || !Client2TestEquipment)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Equipment missing from level"));
	}

	if ((ServerTestEquipment->GetWorldMesh()->GetVisibleFlag() != true) ||
		(Client1TestEquipment->GetWorldMesh()->GetVisibleFlag() != true) ||
		(Client2TestEquipment->GetWorldMesh()->GetVisibleFlag() != true))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}

	Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));
	Locker->SetEquipmentAtIndex(ServerTestEquipment, 0U);

	FTimerHandle StorageHandle;
	GetWorldTimerManager().SetTimer(StorageHandle, this, &ThisClass::AfterEquipmentStore, 1.0f, false);
}

void ALockerStorageVisibilityTest::AfterEquipmentStore()
{
	if ((ServerTestEquipment->GetWorldMesh()->GetVisibleFlag() != false) || 
		(Client1TestEquipment->GetWorldMesh()->GetVisibleFlag() != false) ||
		(Client2TestEquipment->GetWorldMesh()->GetVisibleFlag() != false))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}

	Locker->Remove(0U);

	FTimerHandle RemovalHandle;
	GetWorldTimerManager().SetTimer(RemovalHandle, this, &ThisClass::AfterEquipmentRemoval, 1.0f, false);
}

void ALockerStorageVisibilityTest::AfterEquipmentRemoval()
{
	if ((ServerTestEquipment->GetWorldMesh()->GetVisibleFlag() == true) &&
		(Client1TestEquipment->GetWorldMesh()->GetVisibleFlag() == true) &&
		(Client2TestEquipment->GetWorldMesh()->GetVisibleFlag() == true))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}
